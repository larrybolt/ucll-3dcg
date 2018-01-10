#pragma once

#include "pipeline/processor.h"
#include "imaging/ppm-format.h"
#include <string>


namespace raytracer
{
	namespace pipeline
	{
		std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> ppm();
	}
}