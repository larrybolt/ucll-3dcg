#pragma once

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
            math::Matrix4x4 create_transformation(const math::Point3D&, const math::Point3D&, const math::Vector3D&);

            /// <summary>
            /// Actual implementation of cameras. A camera must, given a point in the unit rectangle,
            /// produce rays going through this point. A camera is free to choose how many rays are produced.
            /// When subclassing, only overload one of both enumerate_rays member functions.
            /// </summary>
            class CameraImplementation
            {
            public:
                /// <summary>
                /// Does exactly the same as enumerate_rays, but returns the produces rays in the form of a vector.
                /// It is slightly less efficient, as memory needs to be allocated and freed.
                /// </summary>
                virtual std::vector<math::Ray> enumerate_rays(const math::Point2D& p) const;

                /// <summary>
                /// Enumerates all rays to be cast from position <paramref name="p" />.
                /// Enumeration happens using a callback: the given function <paramref name="callback" /> gets
                /// called for each ray. This removes the need for heap allocation and should be more efficient.
                /// </summary>
                /// <param name="p">
                /// Point in the [0,1]x[0,1] rectangle.
                /// </param>
                /// <param name="callback">
                /// Function that will get called for each ray.
                /// </param>
                virtual void enumerate_rays(const math::Point2D& p, std::function<void(const math::Ray&)> callback) const;
            };
        }        
    }

    /// <summary>
    /// Camera wrapper. To access the actual Camera members, use the -&gt; operator. The members
    /// are defined in CameraImplementation.
    /// </summary>
    class Camera
    {
    public:
        explicit Camera(std::shared_ptr<cameras::_private_::CameraImplementation> implementation = nullptr)
            : m_implementation(implementation) { }

        cameras::_private_::CameraImplementation* operator ->() const
        {
            return m_implementation.get();
        }

        explicit operator bool()
        {
            return m_implementation != nullptr;
        }

    private:
        std::shared_ptr<cameras::_private_::CameraImplementation> m_implementation;
    };
}