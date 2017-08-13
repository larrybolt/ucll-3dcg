#pragma once

#include "cameras/camera.h"
#include "math/ray.h"
#include "math/point.h"
#include "math/ray.h"
#include "math/matrix.h"
#include <functional>
#include <memory>
#include <vector>


namespace raytracer
{
    namespace cameras
    {
        namespace _private_
        {
            class DisplaceableCamera : public CameraImplementation
            {
            public:
                void enumerate_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const;

            protected:
                DisplaceableCamera(const math::Matrix4x4&);

                virtual void enumerate_untransformed_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const = 0;

            private:
                math::Matrix4x4 m_transformation;
            };
        }
    }
}