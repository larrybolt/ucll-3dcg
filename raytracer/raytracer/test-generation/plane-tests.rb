require './shared.rb'


test_file 'primitives/plane/xy-plane' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "primitives/primitives.h"
      #include "math/approx.h"

      using namespace math;
      using namespace raytracer;
      using namespace raytracer::primitives;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Plane] Hit between XY plane and #{ray_origin} + #{ray_direction} * t", "[Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xy_plane();
            Ray ray(ray_origin, ray_direction);

            Hit hit;

            REQUIRE(primitive->find_first_positive_hit(ray, &hit));
            CHECK(hit.t == Approx(#{expected_t}));
            CHECK(hit.position == approx(Point3D#{expected_hit_position}));
            CHECK(hit.normal == approx(Vector3D#{expected_normal_position}.normalized()));
        }
      END
    end

    [-2,0,2].each do |x|
      [-2,0,2].each do |y|
        [1,5,10].each do |z|
          [1.0,2.0].each do |dz|
            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(0,0,-#{dz})"
              data.expected_t = z / dz
              data.expected_hit_position = "(#{x},#{y},0)"
              data.expected_normal_position = "(0,0,1)"
            end

            test_case do |data|
              data.ray_origin = "(#{x},#{y},-#{z})"
              data.ray_direction = "(0,0,#{dz})"
              data.expected_t = z / dz
              data.expected_hit_position = "(#{x},#{y},0)"
              data.expected_normal_position = "(0,0,-1)"
            end

            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(#{dz},0,-#{dz})"
              data.expected_t = z / dz
              data.expected_hit_position = "(#{x+z},#{y},0)"
              data.expected_normal_position = "(0,0,1)"
            end

            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(0,#{dz},-#{dz})"
              data.expected_t = z / dz
              data.expected_hit_position = "(#{x},#{y+z},0)"
              data.expected_normal_position = "(0,0,1)"
            end
          end         
        end
      end
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Plane] No hit between XY plane and #{ray_origin} + #{ray_direction} * t", "[Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xy_plane();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
        }
      END
    end

    [-2,0,2].each do |x|
      [-2,0,2].each do |y|
        [1,5,10].each do |z|
          [0,1,10].each do |dz|
            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(0,0,#{dz})"
            end

            test_case do |data|
              data.ray_origin = "(#{x},#{y},-#{z})"
              data.ray_direction = "(0,0,-#{dz})"
            end
          end
        end
      end
    end
  end
end

test_file 'primitives/plane/xz-plane' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "primitives/primitives.h"
      #include "math/approx.h"

      using namespace math;
      using namespace raytracer;
      using namespace raytracer::primitives;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Plane] Hit between XZ plane and #{ray_origin} + #{ray_direction} * t", "[Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xz_plane();
            Ray ray(ray_origin, ray_direction);

            Hit hit;

            REQUIRE(primitive->find_first_positive_hit(ray, &hit));
            CHECK(hit.t == Approx(#{expected_t}));
            CHECK(hit.position == approx(Point3D#{expected_hit_position}));
            CHECK(hit.normal == approx(Vector3D#{expected_normal_position}.normalized()));
        }
      END
    end

    [-2,0,2].each do |x|
      [-2,0,2].each do |z|
        [1,5,10].each do |y|
          [1.0, 2.0].each do |dy|
            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(0,-#{dy},0)"
              data.expected_t = y / dy
              data.expected_hit_position = "(#{x},0,#{z})"
              data.expected_normal_position = "(0,1,0)"
            end

            test_case do |data|
              data.ray_origin = "(#{x},-#{y},#{z})"
              data.ray_direction = "(0,#{dy},0)"
              data.expected_t = y / dy
              data.expected_hit_position = "(#{x},0,#{z})"
              data.expected_normal_position = "(0,-1,0)"
            end

            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(#{dy},-#{dy},0)"
              data.expected_t = y / dy
              data.expected_hit_position = "(#{x+y},0,#{z})"
              data.expected_normal_position = "(0,1,0)"
            end

            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(0,-#{dy},#{dy})"
              data.expected_t = y / dy
              data.expected_hit_position = "(#{x},0,#{z+y})"
              data.expected_normal_position = "(0,1,0)"
            end
          end
        end
      end
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Plane] No hit between XZ plane and #{ray_origin} + #{ray_direction} * t", "[Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xz_plane();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
        }
      END
    end

    [-2,0,2].each do |x|
      [-2,0,2].each do |z|
        [1,5,10].each do |y|
          [0,1,10].each do |dy|
            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(0,#{dy},0)"
            end

            test_case do |data|
              data.ray_origin = "(#{x},-#{y},#{z})"
              data.ray_direction = "(0,-#{dy},0)"
            end
          end
        end
      end
    end
  end
end

test_file 'primitives/plane/yz-plane' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "primitives/primitives.h"
      #include "math/approx.h"

      using namespace math;
      using namespace raytracer;
      using namespace raytracer::primitives;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Plane] Hit between YZ plane and #{ray_origin} + #{ray_direction} * t", "[Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::yz_plane();
            Ray ray(ray_origin, ray_direction);

            Hit hit;

            REQUIRE(primitive->find_first_positive_hit(ray, &hit));
            CHECK(hit.t == Approx(#{expected_t}));
            CHECK(hit.position == approx(Point3D#{expected_hit_position}));
            CHECK(hit.normal == approx(Vector3D#{expected_normal_position}.normalized()));
        }
      END
    end

    [-2,0,2].each do |y|
      [-2,0,2].each do |z|
        [1,5,10].each do |x|
          [1.0, 2.0].each do |dx|
            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(-#{dx},0,0)"
              data.expected_t = x / dx
              data.expected_hit_position = "(0,#{y},#{z})"
              data.expected_normal_position = "(1,0,0)"
            end

            test_case do |data|
              data.ray_origin = "(-#{x},#{y},#{z})"
              data.ray_direction = "(#{dx},0,0)"
              data.expected_t = x / dx
              data.expected_hit_position = "(0,#{y},#{z})"
              data.expected_normal_position = "(-1,0,0)"
            end

            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(-#{dx},#{dx},0)"
              data.expected_t = x / dx
              data.expected_hit_position = "(0,#{x+y},#{z})"
              data.expected_normal_position = "(1,0,0)"
            end

            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(-#{dx},0,#{dx})"
              data.expected_t = x / dx
              data.expected_hit_position = "(0,#{y},#{z+x})"
              data.expected_normal_position = "(1,0,0)"
            end
          end
        end
      end
    end
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[Plane] No hit between YZ plane and #{ray_origin} + #{ray_direction} * t", "[Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::yz_plane();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
        }
      END
    end

    [-2,0,2].each do |y|
      [-2,0,2].each do |z|
        [1,5,10].each do |x|
          [0,1,10].each do |dx|
            test_case do |data|
              data.ray_origin = "(#{x},#{y},#{z})"
              data.ray_direction = "(#{dx},0,0)"
            end

            test_case do |data|
              data.ray_origin = "(-#{x},#{y},#{z})"
              data.ray_direction = "(-#{dx},0,0)"
            end
          end
        end
      end
    end
  end
end
