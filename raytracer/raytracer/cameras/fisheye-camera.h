#pragma once

#include "cameras/displaceable-camera.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/point.h"
#include "math/rectangle3d.h"
#include "math/angle.h"

#include <memory>


namespace raytracer
{
	namespace cameras
	{
		namespace _private_
		{
			class FisheyeCamera : public DisplaceableCamera
			{
			public:
				FisheyeCamera(const math::Matrix4x4 transformation, const math::Rectangle3D&);

			protected:
				void enumerate_untransformed_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const;

			private:
				math::Rectangle3D m_view_window;
			};
		}

		/// <summary>
		/// Creates a perspective camera.
		/// </summary>
		/// <param name="eye">The camera's location</param>
		/// <param name="look_at">The point the camera is directed at</param>
		/// <param name="up">Specifies how the camera is tilted sideways. (0,1,0) is standard.</param>
		/// <param name="distance">Distance between eye and view plane.</param>
		Camera fisheye(
			const math::Point3D& eye,
			const math::Point3D& look_at,
			const math::Vector3D& up,
			math::Angle vertical_angle,
			math::Angle horizontal_angle);
	}
}