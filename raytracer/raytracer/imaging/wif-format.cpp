#include "wif-format.h"
#include "easylogging++.h"

using namespace imaging;

namespace
{
    struct RGBColor
    {
        uint8_t r, g, b;

        RGBColor(const Color& c)
        {
            Color clamped = c.clamped();

            r = uint8_t(clamped.r * 255);
            g = uint8_t(clamped.g * 255);
            b = uint8_t(clamped.b * 255);
        }
    };
}


imaging::WIF::WIF(const std::string& path)
    : out(path, std::ios::binary), m_frame_index(0)
{
    // NOP
}

imaging::WIF::~WIF()
{
    uint32_t datum = 0;

    out.write(reinterpret_cast<char*>(&datum), sizeof(uint32_t));
}

void imaging::WIF::write_frame(const Bitmap& bitmap)
{
    LOG(INFO) << "Writing WIF frame #" << m_frame_index;        

    uint32_t width = bitmap.width();
    uint32_t height = bitmap.height();   

    out.write(reinterpret_cast<char*>(&width), sizeof(uint32_t));
    out.write(reinterpret_cast<char*>(&height), sizeof(uint32_t));

    for (unsigned j = 0; j != bitmap.height(); ++j)
    {
        for (unsigned i = 0; i != bitmap.width(); ++i)
        {
            RGBColor RGBColor(bitmap[Position2D(i, j)]);

            out.write(reinterpret_cast<char*>(&RGBColor), sizeof(RGBColor));
        }
    }

    ++m_frame_index;
}

template<typename T>
void write_to_buffer(const T& value, std::vector<uint8_t>& buffer)
{
    auto bytes = reinterpret_cast<const uint8_t*>(&value);

    for (size_t i = 0; i != sizeof(T); ++i)
    {
        buffer.push_back(bytes[i]);
    }
}

void imaging::wif::convert_frame(std::vector<uint8_t>& buffer, const Bitmap& bitmap)
{
    uint32_t width = bitmap.width();
    uint32_t height = bitmap.height();

    write_to_buffer(width, buffer);
    write_to_buffer(height, buffer);

    for (unsigned j = 0; j != bitmap.height(); ++j)
    {
        for (unsigned i = 0; i != bitmap.width(); ++i)
        {
            RGBColor color(bitmap[Position2D(i, j)]);

            write_to_buffer(color, buffer);
        }
    }
}

void imaging::wif::mark_eof(std::vector<uint8_t>& buffer)
{
    uint32_t marker = 0;

    write_to_buffer(marker, buffer);
}