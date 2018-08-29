

#include "animation/lissajous.h"

using namespace math;
using namespace std;
using namespace animation;


	 Animation<Point3D> animation::lissajous(const int x_amplitude, const int y_amplitude, const int z_amplitude,const int x_frequency, const int y_frequency, const int z_frequency,
		const Angle x_phase, const Angle y_phase, const Angle z_phase, const Duration& duration) {
		/*int x_amplitude = x;
		int y_amplitude = y;
		int z_amplitude = z;

		int x_frequency = xf;
		int y_frequency = yf;
		int z_frequency = zf;

		const Angle x_phase = ax;
		const Angle y_phase = ay;
		const Angle z_phase = az;

		Duration duration = d;*/

		std::function<Point3D(TimeStamp)> lambda = [x_amplitude, y_amplitude, z_amplitude, x_frequency, y_frequency, z_frequency, x_phase, y_phase, z_phase, duration](TimeStamp now)->Point3D {
			auto t = now.seconds();
			auto valueX = x_amplitude * sin(2 *3.14*x_frequency*now.seconds() + x_phase.radians());
			auto valueY = y_amplitude * sin(2 * 3.14*y_frequency*now.seconds() + y_phase.degrees());
			auto valueZ = z_amplitude * sin(2 * 3.14*z_frequency*now.seconds() + z_phase.degrees());

			return Point3D(valueX, valueY, valueZ);
		};
		return make_animation(from_lambda(lambda), duration);

};

	//float valueX = x_amplitude * sin(2 * M_PI*x_frequency*now + x_phase);
	//Formule
	//y(t) = amplitude * sin(2 * PI * frequency * t + phase)
	//

