require './shared.rb'


test_file 'primitives/cone/cone' do
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
        TEST_CASE("[Cone] Hit between cone along z and #{ray_origin} + #{ray_direction} * t", "[Cone]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::cone_along_z();
            Ray ray(ray_origin, ray_direction);

            Hit hit;

            REQUIRE(primitive->find_first_positive_hit(ray, &hit));
            CHECK(hit.t == Approx(#{expected_t}));
            CHECK(hit.position == approx(Point3D#{expected_hit_position}));
            CHECK(hit.normal == approx(Vector3D#{expected_normal_position}.normalized()));
        }
      END
    end

    test_case do |data|
      data.ray_origin = '(10,0,1)'
      data.ray_direction = '(-1,0,0)'
      data.expected_t = '9'
      data.expected_hit_position = '(1,0,1)'
      data.expected_normal_position = '(1,0,-1)'
    end

    test_case do |data|
      data.ray_origin = '(-10,0,1)'
      data.ray_direction = '(1,0,0)'
      data.expected_t = '9'
      data.expected_hit_position = '(-1,0,1)'
      data.expected_normal_position = '(-1,0,-1)'
    end

    test_case do |data|
      data.ray_origin = '(7,0,1)'
      data.ray_direction = '(-1,0,0)'
      data.expected_t = '6'
      data.expected_hit_position = '(1,0,1)'
      data.expected_normal_position = '(1,0,-1)'
    end
    
    test_case do |data|
      data.ray_origin = '(7,0,2)'
      data.ray_direction = '(-1,0,0)'
      data.expected_t = '5'
      data.expected_hit_position = '(2,0,2)'
      data.expected_normal_position = '(1,0,-1)'
    end

    test_case do |data|
      data.ray_origin = '(7,0,3)'
      data.ray_direction = '(-1,0,0)'
      data.expected_t = '4'
      data.expected_hit_position = '(3,0,3)'
      data.expected_normal_position = '(1,0,-1)'
    end

    test_case do |data|
      data.ray_origin = '(0,5,3)'
      data.ray_direction = '(0,-1,0)'
      data.expected_t = '2'
      data.expected_hit_position = '(0,3,3)'
      data.expected_normal_position = '(0,1,-1)'
    end

    test_case do |data|
      data.ray_origin = '(0,7,3)'
      data.ray_direction = '(0,-2,0)'
      data.expected_t = '2'
      data.expected_hit_position = '(0,3,3)'
      data.expected_normal_position = '(0,1,-1)'
    end
    
    test_case do |data|
      data.ray_origin = '(0,7,1)'
      data.ray_direction = '(0,-2,0)'
      data.expected_t = '3'
      data.expected_hit_position = '(0,1,1)'
      data.expected_normal_position = '(0,1,-1)'
    end

    test_case do |data|
      data.ray_origin = '(0,-7,1)'
      data.ray_direction = '(0,2,0)'
      data.expected_t = '3'
      data.expected_hit_position = '(0,-1,1)'
      data.expected_normal_position = '(0,-1,-1)'
    end

    test_case do |data|
      data.ray_origin = '(0,-7,-1)'
      data.ray_direction = '(0,2,0)'
      data.expected_t = '3'
      data.expected_hit_position = '(0,-1,-1)'
      data.expected_normal_position = '(0,-1,1)'
    end

    test_case do |data|
      data.ray_origin = '(0,0,1)'
      data.ray_direction = '(0,1,0)'
      data.expected_t = '1'
      data.expected_hit_position = '(0,1,1)'
      data.expected_normal_position = '(0,-1,1)'
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Cone] No hit between cone along z and #{ray_origin} + #{ray_direction} * t", "[Cone]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::cone_along_z();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            hit.t = #{t};

            REQUIRE(!primitive->find_first_positive_hit(ray, &hit));
        }
      END
    end

    test_case do |data|
      data.ray_origin = '(10,0,1)'
      data.ray_direction = '(1,0,0)'
      data.t = 100
    end

    test_case do |data|
      data.ray_origin = '(2,0,1)'
      data.ray_direction = '(1,0,0)'
      data.t = 100
    end

    test_case do |data|
      data.ray_origin = '(-2,0,1)'
      data.ray_direction = '(-1,0,0)'
      data.t = 100
    end

    test_case do |data|
      data.ray_origin = '(0,2,1)'
      data.ray_direction = '(0,1,0)'
      data.t = 100
    end

    test_case do |data|
      data.ray_origin = '(0,5,4)'
      data.ray_direction = '(0,1,0)'
      data.t = 100
    end

    test_case do |data|
      data.ray_origin = '(0,-5,4)'
      data.ray_direction = '(0,-1,0)'
      data.t = 100
    end

    test_case do |data|
      data.ray_origin = '(0,0,1)'
      data.ray_direction = '(0,0,1)'
      data.t = 100
    end

    test_case do |data|
      data.ray_origin = '(10,0,1)'
      data.ray_direction = '(-1,0,0)'
      data.t = 5
    end
  end

  
  test_suite do
    template do
      <<-END
        TEST_CASE("[Cone] All hits between cone along z and #{ray_origin} + #{ray_direction} * t", "[Cone]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::cone_along_z();
            Ray ray(ray_origin, ray_direction);
            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 2);
            REQUIRE(hits[0]->t <= hits[1]->t);
            CHECK(hits[0]->t == Approx(#{expected_ts[0]}));
            CHECK(hits[1]->t == Approx(#{expected_ts[1]}));
        }
      END
    end

    test_case do |data|
      data.ray_origin = '(5,0,1)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '4', '6' ]
    end

    test_case do |data|
      data.ray_origin = '(6,0,1)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '5', '7' ]
    end

    test_case do |data|
      data.ray_origin = '(6,0,2)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '4', '8' ]
    end

    test_case do |data|
      data.ray_origin = '(6,0,3)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '3', '9' ]
    end

    test_case do |data|
      data.ray_origin = '(7,0,3)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '4', '10' ]
    end
  end
  
end
