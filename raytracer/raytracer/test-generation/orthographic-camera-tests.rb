require './shared.rb'


test_file 'cameras/orthographic-camera' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "cameras/cameras.h"
      #include <sstream>
      #include <string>

      using namespace math;


      namespace
      {
          void assert_equals(const Point3D& expected, const Point3D& actual)
          {
              INFO("Expected Point3D: " << expected << "\nActual: " << actual);

              REQUIRE(approx(expected) == actual);
          }

          void assert_equals(const Vector3D& expected, const Vector3D& actual)
          {
              INFO("Expected: " << expected << "\nActual: " << actual);

              REQUIRE(approx(expected) == actual);
          }

          std::string show(const Ray& ray)
          {
              std::ostringstream ss;

              ss << ray;

              return ss.str();
          }
      }

      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[OrthographicCamera] Eye = #{eye}), Lookat = #{look_at}, Up = #{up}, Window Width = #{window_width}, Aspect Ratio = #{aspect_ratio}, At #{position}", "[OrthographicCamera]")
        {
            Point3D eye(#{eye});
            Point3D look_at(#{look_at});
            Vector3D up(#{up});
            double window_width = #{window_width};
            double aspect_ratio = #{aspect_ratio};
            Point2D position(#{position});
            Point3D expected_origin(#{expected_origin});
            Vector3D expected_direction(#{expected_direction});

            auto camera = raytracer::cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
            auto rays = camera->enumerate_rays(position);

            REQUIRE(rays.size() == 1);
            auto ray = rays.front();
            INFO( "Actual ray: " + show(ray) + "\\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
            assert_equals(ray.origin, Point3D(expected_origin));
            assert_equals(ray.direction, Vector3D(expected_direction));
        }
      END
    end

    test_case do |data|
       data.eye = '0,0,0'
       data.look_at = '0,0,1'
       data.up = '0,1,0'
       data.window_width = '1'
       data.aspect_ratio = '1'
       data.position = '0.5,0.5'
       data.expected_origin = '0,0,0'
       data.expected_direction = '0,0,1'
    end

    test_case do |data|
       data.eye = '0,0,0'
       data.look_at = '0,0,1'
       data.up = '0,1,0'
       data.window_width = '1'
       data.aspect_ratio = '1'
       data.position = '1,0.5'
       data.expected_origin = '-0.5,0,0'
       data.expected_direction = '0,0,1'
    end

    test_case do |data|
       data.eye = '0,0,0'
       data.look_at = '0,0,1'
       data.up = '0,1,0'
       data.window_width = '1'
       data.aspect_ratio = '1'
       data.position = '0,0.5'
       data.expected_origin = '0.5,0,0'
       data.expected_direction = '0,0,1'
    end

    test_case do |data|
       data.eye = '0,0,0'
       data.look_at = '0,0,1'
       data.up = '0,1,0'
       data.window_width = '1'
       data.aspect_ratio = '1'
       data.position = '0.5,1'
       data.expected_origin = '0,0.5,0'
       data.expected_direction = '0,0,1'
    end

    test_case do |data|
       data.eye = '0,0,0'
       data.look_at = '0,0,1'
       data.up = '0,1,0'
       data.window_width = '1'
       data.aspect_ratio = '1'
       data.position = '0.5,0'
       data.expected_origin = '0,-0.5,0'
       data.expected_direction = '0,0,1'
    end

    test_case do |data|
       data.eye = '1,0,0'
       data.look_at = '1,0,1'
       data.up = '0,1,0'
       data.window_width = '1'
       data.aspect_ratio = '1'
       data.position = '0.5,0.5'
       data.expected_origin = '1,0,0'
       data.expected_direction = '0,0,1'
    end

    test_case do |data|
       data.eye = '-1,0,0'
       data.look_at = '-1,0,1'
       data.up = '0,1,0'
       data.window_width = '1'
       data.aspect_ratio = '1'
       data.position = '0.5,0.5'
       data.expected_origin = '-1,0,0'
       data.expected_direction = '0,0,1'
    end

    test_case do |data|
       data.eye = '-2,0,0'
       data.look_at = '-2,0,1'
       data.up = '0,1,0'
       data.window_width = '1'
       data.aspect_ratio = '1'
       data.position = '0.5,0.5'
       data.expected_origin = '-2,0,0'
       data.expected_direction = '0,0,1'
    end

    test_case do |data|
       data.eye = '0,0,0'
       data.look_at = '1,0,0'
       data.up = '0,1,0'
       data.window_width = '1'
       data.aspect_ratio = '1'
       data.position = '0.5,0.5'
       data.expected_origin = '0,0,0'
       data.expected_direction = '1,0,0'
    end
  end
end
