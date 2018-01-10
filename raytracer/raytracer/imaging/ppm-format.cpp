#include "imaging/ppm-format.h"

namespace imaging
{
	void write_text_ppm(const Bitmap& bitmap, std::ostream& out)
	{
		uint32_t width = bitmap.width();
		uint32_t height = bitmap.height();

		out.write("P3 ", 3);
		out.write(reinterpret_cast<char*>(&width), sizeof(uint32_t));
		out.write(reinterpret_cast<char*>(&height), sizeof(uint32_t));
		out.write("255 ", 4);

		for (unsigned i = 0; i != width; i++)
		{
			for (unsigned j = 0; i != height; j++)
			{
				Color color(bitmap[Position2D(i, j)]);
				out.write(reinterpret_cast<char*>(&color), sizeof(color) + 1);
			}
		}
	}
}

