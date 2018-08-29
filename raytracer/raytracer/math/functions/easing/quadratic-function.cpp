#include "math/functions/easing/quadratic-function.h"
#include "math/interval.h"
#include "animation/animation.h"

#include <assert.h>
using namespace animation;

using namespace std;
using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::quadratic_in()
{
	
	auto a = 0.0;
	auto b = 1.0;

	std::function<double(double)> lambda = [a, b](double t) {
		assert(interval(a, b).contains(t));
		auto x = b * (t /= 1)*t + a;		//quotient   normaliseerd => tss 0&1
		return x;
	};

	return  from_lambda(lambda);

}

//EasingFunction math::functions::easing::quadratic_out2() {
//
////TimeStamp == [now]
//std::function<double(TimeStamp)> lambda = [](TimeStamp now)  {
//	auto tijdNul = now.zero();
//double t=now.seconds();
//auto d=now.from_epoch(Duration::from_seconds(t));
//	
//	assert(interval(0.0, 1.0).contains(t));
//	
//	
//	return  (t /= d.seconds())*t;
//};
//return from_lambda(lambda);
//
//};


inline math::Function<TimeStamp(double)> seconds_to_timestamp()
{
	std::function<TimeStamp(double)> lambda = [](double seconds) -> TimeStamp {
		return TimeStamp::from_epoch(Duration::from_seconds(seconds));
	};

	return math::from_lambda<TimeStamp, double>(lambda);
}



//EasingFunction math::functions::easing::quadratic_in()
//{
//	//t: start time
//	//b: starting value being interpolated
//	//c: change in value
//	//d: duration
//
//	//  /= betekend Assignment by quotient
//
//	//-`t` time, ie the current framenumber
//		//- `b` beginning position or bottom value of the range
//	//	- `c` total change in position or top value of the range
//		//- `d` duration, ie a framecount
//		//1. `t/d` or `t/ = d` normalizes `t` to between 0 and 1
//		//2. `... * c` scales up to the required range value
//		//3. `... + b` adds the initial offset
//
//
//
//
//	/*float Quad::easeIn(float t, float b, float c, float d) {
//		return c * (t /= d)*t + b;
//	}
//	float Quad::easeOut(float t, float b, float c, float d) {
//		return -c * (t /= d)*(t - 2) + b;
//	}
//
//	float Quad::easeInOut(float t, float b, float c, float d) {
//		if ((t /= d / 2) < 1) return ((c / 2)*(t*t)) + b;
//		return -c / 2 * (((t - 2)*(--t)) - 1) + b;*/
//
//		/*
//		originally return -c/2 * (((t-2)*(--t)) - 1) + b;
//
//		I've had to swap (--t)*(t-2) due to diffence in behaviour in
//		pre-increment operators between java and c++, after hours
//		of joy
//		*/
//	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	//  Take a good look at its syntax: it has the form std::function<R(T1, T2, ...)> 
//	//  where T1, T2, … are the parameter types and R is the return type of the function.
//	//!!!!!!!!!!!!!!!!!!!!!!
//	std::function<double(double)> lambda = [Duration d](double t/*now*/,double b/*from*/, double c/*to*/,double d/*seconds*/) {
//
//		return c * (t /= d)*t + b;
//		/*a=
//		
//		timestamp.seconds()
//
//		double x = a * (t*t);
//
//		if (interval(0.0, 1.0).contains(t)) {
//			return t *t + t;
//		}
//		assert(interval(0.0, 1.0).contains(t));
//
//		return t;*/
//	};
//
//	return from_lambda(lambda);
//}
EasingFunction math::functions::easing::quadratic_out()
{
	std::function<double(double)> lambda = [](double t) {
		assert(interval(0.0, 1.0).contains(t));
		return -1 * (t /= 1)*(t - 2) + 0;
		//return t;
	};

	return from_lambda(lambda);
}

EasingFunction math::functions::easing::quadratic_inout()
{
	std::function<double(double)> lambda = [](double t) {
		double x = 0;
		assert(interval(0.0, 1).contains(t));
		//	x= 0.5 * (t /= 0.5)*t + 0;
		if (t < 0.5) { return 0.5 * (t /= 1)*t + 0; }
		
		LOG(INFO) << t;
		

			return  -0.5 * (t/=1)*(t-2) ;
		
		

		//		if ((t /= d / 2) < 1) return ((c / 2)*(t*t)) + b;
		//		return -c / 2 * (((t - 2)*(--t)) - 1) + b;*/
		//
		//		/*
		//		originally return -c/2 * (((t-2)*(--t)) - 1) + b;
	};

	return from_lambda(lambda);
}
