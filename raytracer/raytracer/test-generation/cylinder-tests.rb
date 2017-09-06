require './shared.rb'


test_file 'primitives/cylinder/cylinder-along-x' do
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
        TEST_CASE("[CylinderX] No hit with ray #{ray_origin} + #{ray_direction} * t", "[Cylinder]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto cylinder = raytracer::primitives::cylinder_along_x();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            hit.t = #{t};

            REQUIRE(!cylinder->find_first_positive_hit(ray, &hit));
        }
      END
    end

    test_case do |data|
      data.ray_origin = "(0, 0, 0)"
      data.ray_direction = "(1, 0, 0)"
      data.t = "10000000"
    end

    [1.01, 2, -1.01, -2].each do |y|
      [-1.01,0,2,5].each do |x|
        [-1.01,0,2,5].each do |z|
          [-2,0.5,3].each do |dx|
            [-1,0.1,1,2].each do |dz|
              test_case do |data|
                data.ray_origin = "(#{x}, #{y}, #{z})"
                data.ray_direction = "(#{dx},0,#{dz})"
                data.t = "100000"
              end
            end
          end
        end
      end
    end

    [1.01, 2, -1.01, -2].each do |z|
      [-1.01,0,2,5].each do |y|
        [-1.01,0,2,5].each do |x|
          [-2,0.5,3].each do |dx|
            [-1,0.1,1,2].each do |dy|
              test_case do |data|
                data.ray_origin = "(#{x}, #{y}, #{z})"
                data.ray_direction = "(#{dx},#{dy},0)"
                data.t = "100000"
              end
            end
          end
        end
      end
    end

    test_case do |data|
      data.ray_origin = "(0, 0, 3)"
      data.ray_direction = "(0, 0, -1)"
      data.t = "1"
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[CylinderX] Ray #{ray_origin} + #{ray_direction} * t hits cylinder", "[Cylinder]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto cylinder = raytracer::primitives::cylinder_along_x();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            REQUIRE(cylinder->find_first_positive_hit(ray, &hit));
        }
      END
    end

    [-5,-1,0,2,9].each do |x|
      [-0.99,-0.5,0,0.7].each do |y|
        [1.1,8].each do |z|
          [-1,0,2].each do |dx|
            [-1,-2].each do |dz|
              test_case do |data|
                data.ray_origin = "(#{x},#{y},#{z})"
                data.ray_direction = "(#{dx},0,#{dz})"
              end

              test_case do |data|
                data.ray_origin = "(#{x},#{y},#{-z})"
                data.ray_direction = "(#{dx},0,#{-dz})"
              end
            end
          end
        end
      end
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[CylinderX] First hit with ray #{ray_origin} + #{ray_direction} * t", "[Cylinder]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto cylinder = raytracer::primitives::cylinder_along_x();
            Ray ray(ray_origin, ray_direction);

            Hit hit;

            REQUIRE(cylinder->find_first_positive_hit(ray, &hit));
            CHECK(hit.t == Approx(#{expected_t}));
            CHECK(hit.position == approx(Point3D#{expected_hit_position}));
            CHECK(hit.normal == approx(Vector3D#{expected_normal_position}));
        }
      END
    end

    [-4,1,0,3].each do |x|
      [2,5,10].each do |z|
        [1.0, 2.0].each do |dz|
          test_case do |data|
            data.ray_origin = "(#{x},0,#{z})"
            data.ray_direction = "(0,0,#{-dz})"
            data.expected_t = (z - 1) / dz
            data.expected_hit_position = "(#{x},0,1)"
            data.expected_normal_position = "(0,0,1)"
          end

          test_case do |data|
            data.ray_origin = "(#{x},0,#{-z})"
            data.ray_direction = "(0,0,#{dz})"
            data.expected_t = (z - 1) / dz
            data.expected_hit_position = "(#{x},0,-1)"
            data.expected_normal_position = "(0,0,-1)"
          end
        end
      end
    end

    [-4,1,0,3].each do |x|
      [2,5,10].each do |y|
        [1.0, 2.0].each do |dy|
          test_case do |data|
            data.ray_origin = "(#{x},#{y},0)"
            data.ray_direction = "(0,#{-dy},0)"
            data.expected_t = (y - 1) / dy
            data.expected_hit_position = "(#{x},1,0)"
            data.expected_normal_position = "(0,1,0)"
          end

          test_case do |data|
            data.ray_origin = "(#{x},#{-y},0)"
            data.ray_direction = "(0,#{dy},0)"
            data.expected_t = (y - 1) / dy
            data.expected_hit_position = "(#{x},-1,0)"
            data.expected_normal_position = "(0,-1,0)"
          end
        end
      end
    end
  end
    
  test_suite do
    template do
      <<-END
        TEST_CASE("[CylinderX] All hits with ray #{ray_origin} + #{ray_direction} * t", "[Cylinder]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto cylinder = raytracer::primitives::cylinder_along_x();
            Ray ray(ray_origin, ray_direction);

            auto hits = cylinder->find_all_hits(ray);
            REQUIRE(hits.size() == 2);
            CHECK(hits[0]->t == #{expected_ts[0]});
            CHECK(hits[1]->t == #{expected_ts[1]});
        }
      END
    end
    
    [-5,-1,0,3,8].each do |x|
      [2,5,8].each do |z|
        [1,2].each do |dz|
          test_case do |data|
            data.ray_origin = "(#{x},0,#{z})"
            data.ray_direction = "(0,0,#{-dz})"
            data.expected_ts = [ (z - 1.0) / dz, (z + 1.0) / dz ]
          end
        end
      end
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[CylinderX] Outward pointing normal vector at first hit with ray #{ray_origin} through (0,0,0)", "[Cylinder]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction = Point3D(0,0,0) - ray_origin;

            auto cylinder = raytracer::primitives::cylinder_along_x();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            REQUIRE(cylinder->find_first_positive_hit(ray, &hit));

            Vector3D expected_normal(0, hit.position.y(), hit.position.z());
            CHECK(hit.normal == approx(expected_normal));
        }
      END
    end
    
    [-5, 0, 8].each do |x|
      [-3, 1.4, 6].each do |y|
        [-3, 2, 8].each do |z|
          test_case do |data|
            data.ray_origin = "(#{x},#{y},#{z})"
          end
        end
      end
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[CylinderX] Inward pointing normal vector at first hit with ray #{ray_origin} through (0,0,0)", "[Cylinder]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction = Point3D(0,0,0) - ray_origin;

            auto cylinder = raytracer::primitives::cylinder_along_x();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            REQUIRE(cylinder->find_first_positive_hit(ray, &hit));

            Vector3D expected_normal(0, -hit.position.y(), -hit.position.z());
            CHECK(hit.normal == approx(expected_normal));
        }
      END
    end
    
    [-5, 0, 8].each do |x|
      [-0.3, 0.1].each do |y|
        [-0.1, 0.2].each do |z|
          test_case do |data|
            data.ray_origin = "(#{x},#{y},#{z})"
          end
        end
      end
    end
  end
end
