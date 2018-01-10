#include "imaging/ppm-format.h"

namespace imaging
{
	void write_text_ppm(const Bitmap& bitmap, std::ostream& out)
	{
		uint32_t width = bitmap.width();
		uint32_t height = bitmap.height();

		out << "P3" << "\n"
			<< width << " "
			<< height << "\n"
			<< "255" << "\n"
			;

		for (unsigned i = 0; i != width; i++)
		{
			for (unsigned j = 0; i != height; j++)
			{
				Color color(bitmap[Position2D(i, j)]);
				out << color << " ";
			}
			out << "\n";
		}
	}
}

