#pragma once

#include "math/vector.h"
#include "math/point.h"
#include "math/approx.h"
#include <iostream>
#include <memory>
#include <array>


namespace math
{
    template<unsigned N>
    class Matrix
    {
    public:
        Matrix(std::array<double, N * N>& elements)
            : m_elements(std::make_unique<std::array<double, N * N>>(elements)) { }

        Matrix(std::unique_ptr<std::array<double, N * N>> elements)
            : m_elements(std::move(elements)) { }

        Matrix(const Matrix<N>& m)
            : m_elements(std::make_unique<std::array<double, N * N>>(*m.m_elements)) { }

        Matrix(Matrix<N>&& m)
            : m_elements(std::move(m.m_elements)) { }

        Matrix<N>& operator =(const Matrix<N>& m)
        {
            *m_elements = *m.m_elements;
        }

        double& at(unsigned row, unsigned col)
        {
            return (*m_elements)[row * N + col];
        }

        double at(unsigned row, unsigned col) const
        {
            return (*m_elements)[row * N + col];
        }

    private:
        std::unique_ptr<std::array<double, N * N>> m_elements;
    };

    using Matrix3x3 = Matrix<3>;
    using Matrix4x4 = Matrix<4>;

    template<unsigned N>
    Matrix<N> zero_matrix()
    {
        std::array<double, N * N> elts;

        for (auto i = elts.begin(); i != elts.end(); ++i)
        {
            *i = 0;
        }

        return Matrix<N>(elts);
    }

    template<unsigned N>
    Matrix<N> identity()
    {
        auto result = zero_matrix<N>();

        for (unsigned i = 0; i != N; ++i)
        {
            result.at(i, i) = 1.0;
        }

        return result;
    }

    template<unsigned N>
    Matrix<N> operator *(const Matrix<N>& a, const Matrix<N>& b)
    {
        auto result = zero_matrix<N>();

        for (unsigned row = 0; row != N; ++row)
        {
            for (unsigned col = 0; col != N; ++col)
            {
                double& target = result.at(row, col);
                target = 0;

                for (unsigned i = 0; i != N; ++i)
                {
                    target += a.at(row, i) * b.at(i, col);
                }
            }
        }

        return result;
    }

    Vector2D operator *(const Matrix3x3& a, const Vector2D& v);
    Vector3D operator *(const Matrix4x4& a, const Vector3D& v);
    Point2D operator *(const Matrix3x3& a, const Point2D& p);
    Point3D operator *(const Matrix4x4& a, const Point3D& p);

    template<unsigned N>
    Matrix<N> transpose(const Matrix<N>& m)
    {
        auto result = zero_matrix<N>();

        for (unsigned row = 0; row != N; ++row)
        {
            for (unsigned col = 0; col != N; ++col)
            {
                result.at(row, col) = m.at(col, row);
            }
        }

        return result;
    }

    template<unsigned N>
    std::ostream& operator <<(std::ostream& out, const Matrix<N>&)
    {
        return out << "Matrix<" << N << ">";
    }

    template<unsigned N>
    struct approximately<Matrix<N>>
    {
        Matrix<N> value;
        double epsilon;

        explicit approximately(const Matrix<N>& value, double epsilon = 0.00001)
            :value(value), epsilon(epsilon)
        {
            // NOP
        }

        bool close_enough(const Matrix<N>& other) const
        {
            for (unsigned row = 0; row != N; ++row)
            {
                for (unsigned col = 0; col != N; ++col)
                {
                    if (value.at(row, col) != approx(other.at(row, col), epsilon))
                    {
                        return false;
                    }
                }
            }

            return true;
        }
    };
}