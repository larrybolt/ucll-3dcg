require './shared.rb'


test_file 'primitives/intersection' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "primitives/primitives.h"

      using namespace math;
      using namespace raytracer::primitives;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Intersection] Hits of Sphere#{sphere1_pos} + Sphere#{sphere2_pos} with #{ray_origin}+#{ray_direction}*t", "[Intersection]")
        {
            auto s1 = translate(Vector3D#{sphere1_pos}, sphere());
            auto s2 = translate(Vector3D#{sphere2_pos}, sphere());
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            auto ray = Ray(ray_origin, ray_direction);
            auto i = intersection(s1, s2);
            auto hits = i->find_all_hits(ray);

            REQUIRE(hits.size() == 2);
            REQUIRE(hits[0]->t == Approx(#{expected_ts[0]}));
            REQUIRE(hits[1]->t == Approx(#{expected_ts[1]}));
        }
      END
    end

    test_case do |data|
      data.sphere1_pos = '(0,0,0)'
      data.sphere2_pos = '(0,0,0)'
      data.ray_origin = '(10,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '9', '11' ]
    end

    test_case do |data|
      data.sphere1_pos = '(0,0,0)'
      data.sphere2_pos = '(0,0,0)'
      data.ray_origin = '(5,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '4', '6' ]
    end

    test_case do |data|
      data.sphere1_pos = '(-0.5,0,0)'
      data.sphere2_pos = '(0.5,0,0)'
      data.ray_origin = '(5,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '4.5', '5.5' ]
    end

    test_case do |data|
      data.sphere1_pos = '(-0.25,0,0)'
      data.sphere2_pos = '(0.25,0,0)'
      data.ray_origin = '(5,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '4.25', '5.75' ]
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Intersection] No hits Sphere#{sphere1_pos} + Sphere#{sphere2_pos} with #{ray_origin}+#{ray_direction}*t", "[Intersection]")
        {
            auto s1 = translate(Vector3D#{sphere1_pos}, sphere());
            auto s2 = translate(Vector3D#{sphere2_pos}, sphere());
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            auto ray = Ray(ray_origin, ray_direction);
            auto i = intersection(s1, s2);
            auto hits = i->find_all_hits(ray);

            REQUIRE(hits.size() == 0);
        }
      END
    end

    test_case do |data|
      data.sphere1_pos = '(0,0,0)'
      data.sphere2_pos = '(0,0,0)'
      data.ray_origin = '(10,10,0)'
      data.ray_direction = '(-1,0,0)'
    end

    test_case do |data|
      data.sphere1_pos = '(-2,0,0)'
      data.sphere2_pos = '(2,0,0)'
      data.ray_origin = '(10,0,0)'
      data.ray_direction = '(-1,0,0)'
    end

    test_case do |data|
      data.sphere1_pos = '(0,2,0)'
      data.sphere2_pos = '(0,-2,0)'
      data.ray_origin = '(10,0,0)'
      data.ray_direction = '(-1,0,0)'
    end
  end
end
