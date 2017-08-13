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


test_file 'primitives/sphere/sphere-no-hits' do
  template do
    instance_eval(&file_template)
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Sphere] No hit with ray #{ray_origin} + #{ray_direction} * t", "[Sphere]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto sphere = raytracer::primitives::sphere();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            hit.t = #{t};

            REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
        }
      END
    end

    (-5..5).each do |a|
      (-5..5).each do |b|
        (-5..5).each do |c|
          [1,2].each do |delta|

            u = a / 5.1
            v = b / 5.1

            if u * u + v * v > 1 then
              test_case do |data|
                data.ray_origin = "(#{u}, #{v}, #{c})"
                data.ray_direction = "(0, 0, #{delta})"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{u}, #{v}, #{c})"
                data.ray_direction = "(0, 0, #{-delta})"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{u}, #{c}, #{v})"
                data.ray_direction = "(0, #{delta}, 0)"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{u}, #{c}, #{v})"
                data.ray_direction = "(0, #{-delta}, 0)"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{c}, #{u}, #{v})"
                data.ray_direction = "(#{delta}, 0, 0)"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{c}, #{u}, #{v})"
                data.ray_direction = "(#{-delta}, 0, 0)"
                data.t = 10000
              end
            end
          end
        end
      end
    end

    [2,5,10].each do |a|
      [1,2].each do |delta|
        test_case do |data|
          data.ray_origin = "(0, 0, #{a})"
          data.ray_direction = "(0, 0, #{-delta})"
          data.t = (a - 1.0) / delta - 0.01
        end

        test_case do |data|
          data.ray_origin = "(0, 0, #{-a})"
          data.ray_direction = "(0, 0, #{delta})"
          data.t = (a - 1.0) / delta - 0.01
        end

        test_case do |data|
          data.ray_origin = "(0, #{a}, 0)"
          data.ray_direction = "(0, #{-delta}, 0)"
          data.t = (a - 1.0) / delta - 0.01
        end

        test_case do |data|
          data.ray_origin = "(0, #{-a}, 0)"
          data.ray_direction = "(0, #{delta}, 0)"
          data.t = (a - 1.0) / delta - 0.01
        end
        
        test_case do |data|
          data.ray_origin = "(#{a}, 0, 0)"
          data.ray_direction = "(#{-delta}, 0, 0)"
          data.t = (a - 1.0) / delta - 0.01
        end

        test_case do |data|
          data.ray_origin = "(#{-a}, 0, 0)"
          data.ray_direction = "(#{delta}, 0, 0)"
          data.t = (a - 1.0) / delta - 0.01
        end
      end
    end
  end
end

test_file 'primitives/sphere/sphere-hits' do
  template do
    instance_eval(&file_template)
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Sphere] No hit with ray #{ray_origin} + #{ray_direction} * t", "[Sphere]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto sphere = raytracer::primitives::sphere();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            hit.t = #{t};

            REQUIRE(sphere->find_first_positive_hit(ray, &hit));
        }
      END
    end

    (-5..5).each do |a|
      (-5..5).each do |b|
        (1..5).each do |c|
          [-1,-2].each do |delta|

            u = a / 5.1
            v = b / 5.1

            if u * u + v * v <= 1 then
              test_case do |data|
                data.ray_origin = "(#{u}, #{v}, #{c})"
                data.ray_direction = "(0, 0, #{delta})"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{u}, #{v}, #{-c})"
                data.ray_direction = "(0, 0, #{-delta})"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{u}, #{c}, #{v})"
                data.ray_direction = "(0, #{delta}, 0)"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{u}, #{-c}, #{v})"
                data.ray_direction = "(0, #{-delta}, 0)"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{c}, #{u}, #{v})"
                data.ray_direction = "(#{delta}, 0, 0)"
                data.t = 10000
              end

              test_case do |data|
                data.ray_origin = "(#{-c}, #{u}, #{v})"
                data.ray_direction = "(#{-delta}, 0, 0)"
                data.t = 10000
              end
            end
          end
        end
      end
    end
  end
end

test_file 'primitives/sphere/sphere-full-hit-checks' do
  template do
    instance_eval(&file_template)
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Sphere] First hit with ray #{ray_origin} + #{ray_direction} * t", "[Sphere]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto sphere = raytracer::primitives::sphere();
            Ray ray(ray_origin, ray_direction);

            Hit hit;

            REQUIRE(sphere->find_first_positive_hit(ray, &hit));
            CHECK(hit.t == Approx(#{expected_t}));
            CHECK(hit.position == approx(Point3D#{expected_hit_position}));
            CHECK(hit.normal == approx(Vector3D#{expected_normal}));
            CHECK(hit.local_position.uv == approx(Point2D#{expected_uv}));
            CHECK(hit.local_position.xyz == approx(Point3D#{expected_xyz}));
        }
      END
    end

    test_case do |data|
      data.ray_origin = '(0, 0, 5)'
      data.ray_direction = '(0, 0, -1)'
      data.expected_t = '4'
      data.expected_hit_position = '(0, 0, 1)'
      data.expected_normal = data.expected_hit_position
      data.expected_uv = '(0.75, 0.5)'
      data.expected_xyz = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,0,3)'
      data.ray_direction = '(0,0,-1)'
      data.expected_t = '2'
      data.expected_hit_position = '(0,0,1)'
      data.expected_normal = data.expected_hit_position
      data.expected_uv = '(0.75, 0.5)'
      data.expected_xyz = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,0,-3)'
      data.ray_direction = '(0,0,+1)'
      data.expected_t = '2'
      data.expected_hit_position = '(0,0,-1)'
      data.expected_normal = data.expected_hit_position
      data.expected_uv = '(0.25, 0.5)'
      data.expected_xyz = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(4,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.expected_t = '3'
      data.expected_hit_position = '(1,0,0)'
      data.expected_normal = data.expected_hit_position
      data.expected_uv = '(0, 0.5)'
      data.expected_xyz = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(-8,0,0)'
      data.ray_direction = '(1,0,0)'
      data.expected_t = '7'
      data.expected_hit_position = '(-1,0,0)'
      data.expected_normal = data.expected_hit_position
      data.expected_uv = '(0.5, 0.5)'
      data.expected_xyz = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,4,0)'
      data.ray_direction = '(0,-1,0)'
      data.expected_t = '3'
      data.expected_hit_position = '(0,1,0)'
      data.expected_normal = data.expected_hit_position
      data.expected_uv = '(0, 0)'
      data.expected_xyz = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,-2,0)'
      data.ray_direction = '(0,1,0)'
      data.expected_t = '1'
      data.expected_hit_position = '(0,-1,0)'
      data.expected_normal = data.expected_hit_position
      data.expected_uv = '(0, 1)'
      data.expected_xyz = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,0,0)'
      data.ray_direction = '(0,1,0)'
      data.expected_t = '1'
      data.expected_hit_position = '(0,1,0)'
      data.expected_normal = '(0,-1,0)'
      data.expected_uv = '(0, 0)'
      data.expected_xyz = data.expected_hit_position
    end
  end
end

test_file 'primitives/sphere/sphere-all-hits' do  
  template do
    instance_eval(&file_template)
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Sphere] All hits with ray #{ray_origin} + #{ray_direction} * t", "[Sphere]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            Ray ray(ray_origin, ray_direction);

            auto sphere = raytracer::primitives::sphere();

            auto hits = sphere->find_all_hits(ray);
            REQUIRE(hits.size() == 2);
            CHECK(hits[0]->t == #{expected_ts[0]});
            CHECK(hits[1]->t == #{expected_ts[1]});
        }
      END
    end

    test_case do |data|
      data.ray_origin = '(0,0,5)'
      data.ray_direction = '(0,0,-1)'
      data.expected_ts = [ '4', '6' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,4)'
      data.ray_direction = '(0,0,-1)'
      data.expected_ts = [ '3', '5' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,-5)'
      data.ray_direction = '(0,0,1)'
      data.expected_ts = [ '4', '6' ]
    end
    
    test_case do |data|
      data.ray_origin = '(0,0,-3)'
      data.ray_direction = '(0,0,1)'
      data.expected_ts = [ '2', '4' ]
    end

    test_case do |data|
      data.ray_origin = '(3,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '2', '4' ]
    end

    test_case do |data|
      data.ray_origin = '(-3,0,0)'
      data.ray_direction = '(1,0,0)'
      data.expected_ts = [ '2', '4' ]
    end

    test_case do |data|
      data.ray_origin = '(0,7,0)'
      data.ray_direction = '(0,-1,0)'
      data.expected_ts = [ '6', '8' ]
    end

    test_case do |data|
      data.ray_origin = '(0,-7,0)'
      data.ray_direction = '(0,1,0)'
      data.expected_ts = [ '6', '8' ]
    end

    test_case do |data|
      data.ray_origin = '(0,-7,0)'
      data.ray_direction = '(0,2,0)'
      data.expected_ts = [ '3', '4' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,0)'
      data.ray_direction = '(0,1,0)'
      data.expected_ts = [ '-1', '1' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,0)'
      data.ray_direction = '(0,0,1)'
      data.expected_ts = [ '-1', '1' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,0)'
      data.ray_direction = '(1,0,0)'
      data.expected_ts = [ '-1', '1' ]
    end
  end
end
