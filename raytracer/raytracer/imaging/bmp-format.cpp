#include "imaging/bmp-format.h"
#include "data-structures/array.h"
#include "easylogging++.h"
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <memory>
#include <assert.h>
#include <cstring>

using namespace imaging;


namespace
{
#pragma pack(push, r1, 1)

    struct FILE_HEADER
    {
        uint16_t FileType;     /* File type, always 4D42h ("BM") */
        uint32_t FileSize;     /* Size of the file in bytes */
        uint16_t Reserved1;    /* Always 0 */
        uint16_t Reserved2;    /* Always 0 */
        uint32_t BitmapOffset; /* Starting position of image data in bytes */
    };

    struct BITMAP_HEADER_V2
    {
        uint32_t Size;            /* Size of this header in bytes */
        int32_t  Width;           /* Image width in pixels */
        int32_t  Height;          /* Image height in pixels */
        uint16_t Planes;          /* Number of color planes */
        uint16_t BitsPerPixel;    /* Number of bits per pixel */
    };

    struct BITMAP_HEADER_V3
    {
        uint32_t Size;            /* Size of this header in bytes */
        int32_t  Width;           /* Image width in pixels */
        int32_t  Height;          /* Image height in pixels */
        uint16_t Planes;          /* Number of color planes */
        uint16_t BitsPerPixel;    /* Number of bits per pixel */
        uint32_t Compression;     /* Compression methods used */
        uint32_t SizeOfBitmap;    /* Size of bitmap in bytes */
        int32_t  HorzResolution;  /* Horizontal resolution in pixels per meter */
        int32_t  VertResolution;  /* Vertical resolution in pixels per meter */
        uint32_t ColorsUsed;      /* Number of colors in the image */
        uint32_t ColorsImportant; /* Minimum number of important colors */
    };

    struct BITMAP_HEADER_V4
    {
        uint32_t Size;            /* Size of this header in bytes */
        int32_t  Width;           /* Image width in pixels */
        int32_t  Height;          /* Image height in pixels */
        uint16_t Planes;          /* Number of color planes */
        uint16_t BitsPerPixel;    /* Number of bits per pixel */
        uint32_t Compression;     /* Compression methods used */
        uint32_t SizeOfBitmap;    /* Size of bitmap in bytes */
        int32_t  HorzResolution;  /* Horizontal resolution in pixels per meter */
        int32_t  VertResolution;  /* Vertical resolution in pixels per meter */
        uint32_t ColorsUsed;      /* Number of colors in the image */
        uint32_t ColorsImportant; /* Minimum number of important colors */
        uint32_t RedMask;         /* Mask identifying bits of red component */
        uint32_t GreenMask;       /* Mask identifying bits of green component */
        uint32_t BlueMask;        /* Mask identifying bits of blue component */
        uint32_t AlphaMask;       /* Mask identifying bits of alpha component */
        uint32_t CSType;          /* Color space type */
        int32_t  RedX;            /* X coordinate of red endpoint */
        int32_t  RedY;            /* Y coordinate of red endpoint */
        int32_t  RedZ;            /* Z coordinate of red endpoint */
        int32_t  GreenX;          /* X coordinate of green endpoint */
        int32_t  GreenY;          /* Y coordinate of green endpoint */
        int32_t  GreenZ;          /* Z coordinate of green endpoint */
        int32_t  BlueX;           /* X coordinate of blue endpoint */
        int32_t  BlueY;           /* Y coordinate of blue endpoint */
        int32_t  BlueZ;           /* Z coordinate of blue endpoint */
        uint32_t GammaRed;        /* Gamma red coordinate scale value */
        uint32_t GammaGreen;      /* Gamma green coordinate scale value */
        uint32_t GammaBlue;       /* Gamma blue coordinate scale value */
    };


    struct BITMAP_HEADER_V5
    {
        uint32_t Size;            /* Size of this header in bytes */
        int32_t  Width;           /* Image width in pixels */
        int32_t  Height;          /* Image height in pixels */
        uint16_t Planes;          /* Number of color planes */
        uint16_t BitsPerPixel;    /* Number of bits per pixel */
        uint32_t Compression;     /* Compression methods used */
        uint32_t SizeOfBitmap;    /* Size of bitmap in bytes */
        int32_t  HorzResolution;  /* Horizontal resolution in pixels per meter */
        int32_t  VertResolution;  /* Vertical resolution in pixels per meter */
        uint32_t ColorsUsed;      /* Number of colors in the image */
        uint32_t ColorsImportant; /* Minimum number of important colors */
        uint32_t RedMask;         /* Mask identifying bits of red component */
        uint32_t GreenMask;       /* Mask identifying bits of green component */
        uint32_t BlueMask;        /* Mask identifying bits of blue component */
        uint32_t AlphaMask;       /* Mask identifying bits of alpha component */
        uint32_t CSType;          /* Color space type */
        int32_t  RedX;            /* X coordinate of red endpoint */
        int32_t  RedY;            /* Y coordinate of red endpoint */
        int32_t  RedZ;            /* Z coordinate of red endpoint */
        int32_t  GreenX;          /* X coordinate of green endpoint */
        int32_t  GreenY;          /* Y coordinate of green endpoint */
        int32_t  GreenZ;          /* Z coordinate of green endpoint */
        int32_t  BlueX;           /* X coordinate of blue endpoint */
        int32_t  BlueY;           /* Y coordinate of blue endpoint */
        int32_t  BlueZ;           /* Z coordinate of blue endpoint */
        uint32_t GammaRed;        /* Gamma red coordinate scale value */
        uint32_t GammaGreen;      /* Gamma green coordinate scale value */
        uint32_t GammaBlue;       /* Gamma blue coordinate scale value */
        uint32_t Intent;
        uint32_t ProfileData;
        uint32_t ProfileSize;
        uint32_t Reserved;
    };

    struct BITMAP_FILE_V3
    {
        FILE_HEADER      file_header;
        BITMAP_HEADER_V3 bitmap_header;
    };

    struct BITMAP_FILE_V4
    {
        FILE_HEADER      file_header;
        BITMAP_HEADER_V4 bitmap_header;
    };

    struct BITMAP_FILE_V5
    {
        FILE_HEADER      file_header;
        BITMAP_HEADER_V5 bitmap_header;
    };

    struct ARGB
    {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    };

    struct RGB
    {
        uint8_t b;
        uint8_t g;
        uint8_t r;
    };

#pragma pack(pop, r1)


    ARGB to_argb(const Color& c)
    {
        Color clamped = c.clamped();

        uint8_t a = 255;
        uint8_t r = uint8_t(clamped.r * 255);
        uint8_t g = uint8_t(clamped.g * 255);
        uint8_t b = uint8_t(clamped.b * 255);

        return ARGB{ b, g, r, a };
    }

    Color from_argb(const ARGB& argb)
    {
        double r = argb.r / 255.0;
        double g = argb.g / 255.0;
        double b = argb.b / 255.0;

        return Color{ r, g, b };
    }

    Color from_rgb(const RGB& rgb)
    {
        double r = rgb.r / 255.0;
        double g = rgb.g / 255.0;
        double b = rgb.b / 255.0;

        return Color{ r, g, b };
    }

    unsigned file_size(std::ifstream& in)
    {
        auto position = in.tellg();
        in.seekg(0, std::ios::end);
        auto length = in.tellg();
        in.seekg(position, std::ios::beg);

        return unsigned(length);
    }

    array<uint8_t> read_data(const std::string& path)
    {
        std::ifstream in(path, std::ios::binary);

        if (!in)
        {
            LOG(ERROR) << "Could not open file " << path << std::endl;
            abort();
        }
        else
        {
            unsigned size = file_size(in);
            array<uint8_t> buffer(size);
            in.read(reinterpret_cast<char*>(buffer.ptr()), buffer.size());

            return buffer;
        }
    }

    void verify_file_header(const FILE_HEADER* p)
    {
        if (p->FileType != 0x4D42)
        {
            LOG(ERROR) << "Invalid file type" << std::endl;
            abort();
        }
    }

    void verify_bitmap_header(const BITMAP_HEADER_V5* p)
    {
        if (p->Size != sizeof(BITMAP_HEADER_V5))
        {
            LOG(ERROR) << "Invalid size " << p->Size << ", only support " << sizeof(BITMAP_HEADER_V5) << std::endl;
            abort();
        }

        if (p->Compression != 0)
        {
            LOG(ERROR) << "Unsupported compression " << p->Compression << std::endl;
            abort();
        }

        if (p->Planes != 1)
        {
            LOG(ERROR) << "Unsupported plane count " << p->Planes << std::endl;
            abort();
        }

        if (p->BitsPerPixel != 24 && p->BitsPerPixel != 32)
        {
            LOG(ERROR) << "Unsupported bits per pixel " << p->BitsPerPixel << std::endl;
            abort();
        }

        if (p->Height < 0)
        {
            LOG(ERROR) << "Unsupported height " << p->Height << std::endl;
            abort();
        }
    }

    void read_24bit_pixels(Bitmap& bmp, array<uint8_t> pixels)
    {
        unsigned scanline_size = (bmp.width() * sizeof(RGB) + 3) & 0xFFFFFFFC;

        for (unsigned y = 0; y < bmp.height(); ++y)
        {
            array<uint8_t> scanline = pixels.slice(y * scanline_size);

            for (unsigned x = 0; x != bmp.width(); ++x)
            {
                Position2D p{ x, bmp.height() - y - 1 };
                array<uint8_t> pixelBytes = scanline.slice(x * sizeof(RGB));
                RGB* pixel = reinterpret<RGB>(pixelBytes);

                bmp[p] = from_rgb(*pixel);
            }
        }
    }

    void read_32bit_pixels(Bitmap& bmp, array<uint8_t> pixels)
    {
        for (unsigned y = 0; y < bmp.height(); ++y)
        {
            array<uint8_t> scanline = pixels.slice(y * bmp.width() * sizeof(ARGB));

            for (unsigned x = 0; x != bmp.width(); ++x)
            {
                Position2D p{ x, bmp.height() - y - 1 };
                array<uint8_t> pixelBytes = scanline.slice(x * sizeof(ARGB));
                ARGB* pixel = reinterpret<ARGB>(pixelBytes);

                bmp[p] = from_argb(*pixel);
            }
        }
    }
}

std::shared_ptr<Bitmap> imaging::load_bitmap(const std::string& path)
{
    array<uint8_t> data = read_data(path);
    BITMAP_FILE_V5* file = reinterpret<BITMAP_FILE_V5>(data);

    verify_file_header(&file->file_header);
    verify_bitmap_header(&file->bitmap_header);

    unsigned width = std::abs(file->bitmap_header.Width);
    unsigned height = std::abs(file->bitmap_header.Height);

    auto bitmap = std::make_shared<Bitmap>(width, height);

    array<uint8_t> pixels = data.slice(file->file_header.BitmapOffset);

    switch (file->bitmap_header.BitsPerPixel)
    {
    case 24:
        read_24bit_pixels(*bitmap, pixels);
        break;

    case 32:
        read_32bit_pixels(*bitmap, pixels);
        break;

    default:
        abort();
    }

    return bitmap;
}

void imaging::save_bitmap(const std::string& path, const Bitmap& bitmap)
{
    BITMAP_FILE_V5 header;
    memset(&header, 0, sizeof(header));

    header.file_header.FileType = 0x4D42;
    header.file_header.FileSize = sizeof(BITMAP_FILE_V5) + 4 * bitmap.width() * bitmap.height();
    header.file_header.Reserved1 = 0;
    header.file_header.Reserved2 = 0;
    header.file_header.BitmapOffset = sizeof(BITMAP_FILE_V5);

    header.bitmap_header.Size = sizeof(BITMAP_HEADER_V5);
    header.bitmap_header.Width = bitmap.width();
    header.bitmap_header.Height = bitmap.height();
    header.bitmap_header.Planes = 1;
    header.bitmap_header.BitsPerPixel = 32;
    header.bitmap_header.Compression = 0;
    header.bitmap_header.SizeOfBitmap = 0;
    header.bitmap_header.HorzResolution = 3779;
    header.bitmap_header.VertResolution = 3779;
    header.bitmap_header.ColorsUsed = 0;
    header.bitmap_header.ColorsImportant = 0;
    header.bitmap_header.RedMask = 0x00FF0000;
    header.bitmap_header.GreenMask = 0x0000FF00;
    header.bitmap_header.BlueMask = 0x000000FF;
    header.bitmap_header.AlphaMask = 0xFF000000;
    header.bitmap_header.CSType = 0x73524742;
    header.bitmap_header.Intent = 4;

    std::ofstream out(path, std::ios::binary);
    out.write(reinterpret_cast<char*>(&header), sizeof(header));

    std::unique_ptr<ARGB[]> scanline = std::make_unique<ARGB[]>(bitmap.width());

    for (int y = bitmap.height() - 1; y >= 0; --y)
    {
        for (unsigned x = 0; x < bitmap.width(); ++x)
        {
            Position2D pos(x, y);

            scanline[x] = to_argb(bitmap[pos]);
        }

        out.write(reinterpret_cast<char*>(scanline.get()), sizeof(ARGB) * bitmap.width());
    }
}
