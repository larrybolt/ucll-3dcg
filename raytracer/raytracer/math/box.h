#pragma once

#include "math/interval.h"
#include "math/ray.h"


namespace math
{
    class Box
    {
    public:
        Box(const Interval<double>&, const Interval<double>&, const Interval<double>&);
        
        static Box empty();
        static Box infinite();
        static Box from_raw_corners(const Point3D&, const Point3D&);
        static Box from_corners(const Point3D&, const Point3D&);

        Interval<double> x() const;
        Interval<double> y() const;
        Interval<double> z() const;

        bool is_infinite() const;

        bool is_hit_positively_by(const math::Ray&) const;
        bool is_hit_by(const math::Ray&) const;

        Box merge(const Box&) const;
        Box intersect(const Box&) const;

        template<unsigned I, unsigned J, unsigned K>
        Point3D corner() const
        {
            static_assert(I == 0 || I == 1, "I must be either 0 or 1");
            static_assert(J == 0 || J == 1, "J must be either 0 or 1");
            static_assert(K == 0 || K == 1, "K must be either 0 or 1");

            return Point3D(m_x_interval.bound<I>(), m_y_interval.bound<J>(), m_z_interval.bound<K>());
        }

        Point3D center() const;

        bool contains(const Point3D&) const;

    private:
        bool hits_xy_face(const Ray&, double, bool) const;
        bool hits_xz_face(const Ray&, double, bool) const;
        bool hits_yz_face(const Ray&, double, bool) const;

        Interval<double> m_x_interval, m_y_interval, m_z_interval;
    };
}
