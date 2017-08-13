#include "cameras/camera.h"
#include "math/transformation-matrices.h"
#include "easylogging++.h"
#include <assert.h>

using namespace math;


Matrix4x4 raytracer::cameras::_private_::create_transformation(const Point3D& eye, const Point3D& look_at, const Vector3D& up)
{
    if (!up.is_unit())
    {
        LOG(ERROR) << "Camera's up vector should have length 1";
        abort();
    }

    Vector3D look_direction = (look_at - eye).normalized();
    Vector3D right = look_direction.cross(up).normalized();
    Vector3D fixed_up = right.cross(look_direction);

    assert(look_direction.is_unit());
    assert(right.is_unit());
    assert(fixed_up.is_perpendicular_on(right));
    assert(look_direction.is_perpendicular_on(right));

    Point3D origin = eye;
    Vector3D y_axis = fixed_up;
    Vector3D z_axis = look_direction;
    Vector3D x_axis = y_axis.cross(z_axis);

    assert(x_axis.is_unit());
    assert(y_axis.is_unit());
    assert(z_axis.is_unit());
    assert(x_axis.is_perpendicular_on(y_axis));
    assert(x_axis.is_perpendicular_on(z_axis));
    assert(y_axis.is_perpendicular_on(z_axis));

    Matrix4x4 transformation = math::transformation_matrices::coordinate_system(origin, x_axis, y_axis, z_axis);

    assert(transformation * Vector3D(0, 1, 0) == approx(fixed_up));
    assert(transformation * Vector3D(0, 0, 1) == approx(look_direction));

    return transformation;
}

std::vector<Ray> raytracer::cameras::_private_::CameraImplementation::enumerate_rays(const math::Point2D& p) const
{
    std::vector<Ray> rays;

    // Call other overload. The given function is called once for each ray.
    this->enumerate_rays(p, [&rays](const Ray& ray)
    {
        // Add each ray to vector
        rays.push_back(ray);
    });

    // Return all rays
    return rays;
}

void raytracer::cameras::_private_::CameraImplementation::enumerate_rays(const math::Point2D& p, std::function<void(const math::Ray&)> callback) const
{
    // Call other overload
    auto rays = enumerate_rays(p);

    // Iterate over rays
    for (auto& ray : rays)
    {
        // Pass each ray to callback
        callback(ray);
    }
}