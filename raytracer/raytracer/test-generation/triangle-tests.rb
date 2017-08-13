require './shared.rb'

file_template = proc do
  <<-'END'
    #ifdef TEST_BUILD

    #include "Catch.h"
    #include "primitives/primitives.h"
    #include "math/approx.h"
    #include <algorithm>

    using namespace math;
    using namespace raytracer;
    using namespace raytracer::primitives;


    <<<TESTS>>>

    #endif
  END
end  


test_file 'primitives/triangle/triangle-hits' do
  template do
    instance_eval(&file_template)
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] No hit between Triangle[#{a}, #{b}, #{c}] and ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
        {
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto triangle = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            hit.t = #{t};

            REQUIRE(!triangle->find_first_positive_hit(ray, &hit));
        }
      END
    end

    test_case do |data|
      data.a = "(0, 0, 0)"
      data.b = "(1, 0, 0)"
      data.c = "(1, 0, 1)"
      data.ray_origin = "(0, 1, 0)"
      data.ray_direction = "(0, 0, 1)"
      data.t = "std::numeric_limits<double>::infinity()"
    end

    test_case do |data|
      data.a = "(0, 0, 0)"
      data.b = "(1, 1, 0)"
      data.c = "(1, 0, 1)"
      data.ray_origin = "(0, 2, 0)"
      data.ray_direction = "(0, 0, 1)"
      data.t = "std::numeric_limits<double>::infinity()"
    end

    test_case do |data|
      data.a = "(5, 5, 0)"
      data.b = "(5, 6, 0)"
      data.c = "(6, 6, 0)"
      data.ray_origin = "(0, 0, 0)"
      data.ray_direction = "(0, 0, 1)"
      data.t = "std::numeric_limits<double>::infinity()"
    end

    test_case do |data|
      data.a = "(-5, 5, 0)"
      data.b = "(5, 0, 0)"
      data.c = "(-5, -5, 0)"
      data.ray_origin = "(0, 0, 0)"
      data.ray_direction = "(0, 0, 1)"
      data.t = "1"
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Hit between Triangle[#{a}, #{b}, #{c}] and ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
        {
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto triangle = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            hit.t = #{t};

            REQUIRE(triangle->find_first_positive_hit(ray, &hit));
        }
      END
    end

    test_case do |data|
      data.a = "(-1, -1, 0)"
      data.b = "(-1, 1, 0)"
      data.c = "(1, 0, 0)"
      data.ray_origin = "(0, 0, -5)"
      data.ray_direction = "(0, 0, 1)"
      data.t = "std::numeric_limits<double>::infinity();"
    end

    test_case do |data|
      data.a = "(-1, -1, 0)"
      data.b = "(1, 0, 0)"
      data.c = "(-1, 1, 0)"
      data.ray_origin = "(0, 0, 5)"
      data.ray_direction = "(0, 0, -1)"
      data.t = "std::numeric_limits<double>::infinity();"
    end

    test_case do |data|
      data.a = "(-1, -1, 0)"
      data.b = "(1, 0, 4)"
      data.c = "(-1, 1, 0)"
      data.ray_origin = "(0, 0, 5)"
      data.ray_direction = "(0, 0, -1)"
      data.t = "std::numeric_limits<double>::infinity();"
    end

    test_case do |data|
      data.a = "(-1, 0, 1)"
      data.b = "(1, 0, 1)"
      data.c = "(0, 0, -10)"
      data.ray_origin = "(0, 5, 0)"
      data.ray_direction = "(0, -5, 0)"
      data.t = "std::numeric_limits<double>::infinity();"
    end

    test_case do |data|
      data.a = "(-1, 0, -1)"
      data.b = "(1, 0, -1)"
      data.c = "(0, 0, 10)"
      data.ray_origin = "(0, 5, 0)"
      data.ray_direction = "(0, -5, 0)"
      data.t = "std::numeric_limits<double>::infinity();"
    end

    test_case do |data|
      data.a = "(-1, 0, 1)"
      data.b = "(1, 0, 1)"
      data.c = "(0, 0, -10)"
      data.ray_origin = "(0, -5, 0)"
      data.ray_direction = "(0, 5, 0)"
      data.t = "std::numeric_limits<double>::infinity();"
    end

    test_case do |data|
      data.a = "(-1, -1, 0)"
      data.b = "(-1, 1, 0)"
      data.c = "(1, 0, 0)"
      data.ray_origin = "(0, 0, 5)"
      data.ray_direction = "(0, 0, -1)"
      data.t = "std::numeric_limits<double>::infinity();"
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Hit normal between Triangle[#{a}, #{b}, #{c}] and ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
        {
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            Vector3D expected_normal#{expected_normal};

            auto triangle = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            hit.t = #{t};

            REQUIRE(triangle->find_first_positive_hit(ray, &hit));
            REQUIRE(hit.normal == approx(expected_normal));
        }
      END
    end

    test_case do |data|
      data.a = "(-1, -1, 0)"
      data.b = "(-1, 1, 0)"
      data.c = "(1, 0, 0)"
      data.ray_origin = "(0, 0, -5)"
      data.ray_direction = "(0, 0, 1)"
      data.t = "std::numeric_limits<double>::infinity();"
      
      data.expected_normal = "(0, 0, -1)"
    end

    test_case do |data|
      data.a = "(-1, -1, 0)"
      data.b = "(-1, 1, 0)"
      data.c = "(1, 0, 0)"
      data.ray_origin = "(0, 0, 5)"
      data.ray_direction = "(0, 0, -1)"
      data.t = "std::numeric_limits<double>::infinity();"
      
      data.expected_normal = "(0, 0, 1)"
    end

    test_case do |data|
      data.a = "(-5, 0, -3)"
      data.b = "(-2, 0, 8)"
      data.c = "(10, 0, 0)"
      data.ray_origin = "(0, 5, 0)"
      data.ray_direction = "(0, -1, 0)"
      data.t = "std::numeric_limits<double>::infinity();"
      
      data.expected_normal = "(0, 1, 0)"
    end

    test_case do |data|
      data.a = "(-5, 0, -3)"
      data.b = "(-2, 0, 8)"
      data.c = "(10, 0, 0)"
      data.ray_origin = "(0, -5, 0)"
      data.ray_direction = "(0, 1, 0)"
      data.t = "std::numeric_limits<double>::infinity();"
      
      data.expected_normal = "(0, -1, 0)"
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Hit t between Triangle[#{a}, #{b}, #{c}] and ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
        {
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            double expected_t = #{expected_t};

            auto triangle = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            hit.t = #{t};

            REQUIRE(triangle->find_first_positive_hit(ray, &hit));
            REQUIRE(hit.t == approx(expected_t));
        }
      END
    end

    test_case do |data|
      data.a = "(-1, -1, 0)"
      data.b = "(-1, 1, 0)"
      data.c = "(1, 0, 0)"
      data.ray_origin = "(0, 0, -5)"
      data.ray_direction = "(0, 0, 1)"
      data.t = "std::numeric_limits<double>::infinity();"
      
      data.expected_t = "(0, 0, 5)"
    end

    test_case do |data|
      data.a = "(-1, -1, 0)"
      data.b = "(-1, 1, 0)"
      data.c = "(1, 0, 0)"
      data.ray_origin = "(0, 0, 10)"
      data.ray_direction = "(0, 0, -1)"
      data.t = "std::numeric_limits<double>::infinity();"
      
      data.expected_t = "(0, 0, 10)"
    end
  end
end
