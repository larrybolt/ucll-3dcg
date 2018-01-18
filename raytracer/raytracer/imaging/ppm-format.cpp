#include "imaging/ppm-format.h"
#include <bitset>

using namespace imaging;

namespace
{
	struct RGBColor
	{
		double r, g, b;

		RGBColor(const Color& c)
		{
			Color clamped = c.clamped();

			r = floor(clamped.r * 255);
			g = floor(clamped.g * 255);
			b = floor(clamped.b * 255);
		}
	};
}

namespace imaging
{
	void write_text_ppm(const Bitmap& bitmap, std::ostream& out)
	{
		int width = bitmap.width();
		int height = bitmap.height();

		// Ppm header
		out << "P3\n"
			<< width << " " << height << "\n"
			<< "255\n"
			;

		// Ppm payload
		// Each line is a row of pixels with its rgb values seperated by whitespace
		for (unsigned j = 0; j != height; j++)
		{
			for (unsigned i = 0; i != width; i++)
			{
				Color color(bitmap[Position2D(i, j)]);
				RGBColor rgb(color);
				out << rgb.r << " " << rgb.g << " " << rgb.b << "	";
			}
			out << "\n";
		}
	}
}