#include "cameras/displaceable-camera.h"
#include <assert.h>

using namespace math;


raytracer::cameras::_private_::DisplaceableCamera::DisplaceableCamera(const Matrix4x4& transformation)
    : m_transformation(transformation)
{
    // NOP
}

void raytracer::cameras::_private_::DisplaceableCamera::enumerate_rays(const math::Point2D& p, std::function<void(const math::Ray&)> callback) const
{
    enumerate_untransformed_rays(p, [this, &callback](const Ray& untransformed_ray) {
        auto transformed_ray = untransformed_ray.transform(m_transformation);

        callback(transformed_ray);
    });
}