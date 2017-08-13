require './shared.rb'


test_file 'primitives/difference/difference' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "primitives/primitives.h"

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
        TEST_CASE("[Difference] Hits of Sphere#{sphere1_pos} - Sphere#{sphere2_pos} with #{ray_origin}+#{ray_direction}*t", "[Difference]")
        {
            auto s1 = translate(Vector3D#{sphere1_pos}, sphere());
            auto s2 = translate(Vector3D#{sphere2_pos}, sphere());
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            auto ray = Ray(ray_origin, ray_direction);
            auto primitive = difference(s1, s2);
            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 2);
            CHECK(hits[0]->t == Approx(#{expected_ts[0]}));
            CHECK(hits[1]->t == Approx(#{expected_ts[1]}));
        }

        TEST_CASE("[Difference] First hit check of Sphere#{sphere1_pos} - Sphere#{sphere2_pos} with #{ray_origin}+#{ray_direction}*t", "[Difference]")
        {
            auto s1 = translate(Vector3D#{sphere1_pos}, sphere());
            auto s2 = translate(Vector3D#{sphere2_pos}, sphere());
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            auto ray = Ray(ray_origin, ray_direction);
            auto primitive = difference(s1, s2);

            Hit hit;
            REQUIRE(primitive->find_first_positive_hit(ray, &hit));
            CHECK(hit.normal == approx(Vector3D#{normal}));
        }
      END
    end

    [2, 5, 10].each do |z|
      test_case do |data|
        data.sphere1_pos = "(0,0,0.5)"
        data.sphere2_pos = "(0,0,-0.5)"
        data.ray_origin = "(0,0,#{z})"
        data.ray_direction = "(0,0,-1)"
        data.expected_ts = [ "#{z - 1.5}", "#{z - 0.5}" ]
        data.normal = "(0,0,1)"
      end

      test_case do |data|
        data.sphere1_pos = "(0,0,0.5)"
        data.sphere2_pos = "(0,0,-0.5)"
        data.ray_origin = "(0,0,#{-z})"
        data.ray_direction = "(0,0,1)"
        data.expected_ts = [ "#{z + 0.5}", "#{z + 1.5}" ]
        data.normal = "(0,0,-1)"
      end
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Difference] Zero hits Sphere#{sphere1_pos} - Sphere#{sphere2_pos} with #{ray_origin}+#{ray_direction}*t", "[Intersection]")
        {
            auto s1 = translate(Vector3D#{sphere1_pos}, sphere());
            auto s2 = translate(Vector3D#{sphere2_pos}, sphere());
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            auto ray = Ray(ray_origin, ray_direction);
            auto i = difference(s1, s2);
            auto hits = i->find_all_hits(ray);

            REQUIRE(hits.size() == 0);
        }

        TEST_CASE("[Difference] No first hit Sphere#{sphere1_pos} - Sphere#{sphere2_pos} with #{ray_origin}+#{ray_direction}*t", "[Intersection]")
        {
            auto s1 = translate(Vector3D#{sphere1_pos}, sphere());
            auto s2 = translate(Vector3D#{sphere2_pos}, sphere());
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            auto ray = Ray(ray_origin, ray_direction);
            auto primitive = difference(s1, s2);

            Hit hit;
            REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
        }
      END
    end

    
    test_case do |data|
      data.sphere1_pos = '(0,0,0)'
      data.sphere2_pos = '(0,0,0)'
      data.ray_origin = '(0,0,10)'
      data.ray_direction = '(0,0,-1)'
    end

    test_case do |data|
      data.sphere1_pos = '(0,0,0)'
      data.sphere2_pos = '(0,0,0)'
      data.ray_origin = '(0,0,5)'
      data.ray_direction = '(0,0,-1)'
    end
    
  end
  
  
end
