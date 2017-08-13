require './shared.rb'

file_template = proc do
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


test_file 'primitives/union/union-hit-count' do
  template do
    instance_eval(&file_template)
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Union] Counting hits of Sphere#{center1} + Sphere#{center2} with #{ray_origin} + #{ray_direction} * t", "[Union]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto sphere1 = translate( Vector3D#{center1}, sphere() );
            auto sphere2 = translate( Vector3D#{center2}, sphere() );
            std::vector<Primitive> primitives = { sphere1, sphere2 };
            auto primitive = make_union( primitives );
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == #{expected_hit_count});
        }
      END
    end

    (-2..2).each do |c1|
      (-2..2).each do |c2|
        test_case do |data|
          data.ray_origin = "(-100, 0, 0)"
          data.ray_direction = "(1, 0, 0)"
          data.center1 = "(#{c1}, 0, 0)"
          data.center2 = "(#{c2}, 0, 0)"
          data.expected_hit_count = if (c1 - c2).abs <= 2 then 2 else 4 end
        end
      end
    end

    [-5, -0.99, -0.1, 0.5, 0.99, 5].each do |y|
      [-9, -0.99, -0.2, 0.3, 0.99, 7].each do |z|
        (-2..2).each do |c1|
          [2.1, 5, 10].each do |delta_c|
            test_case do |data|
              c2 = c1 + delta_c
              
              data.ray_origin = "(-100, #{y}, #{z})"
              data.ray_direction = "(1, 0, 0)"
              data.center1 = "(#{c1}, 0, 0)"
              data.center2 = "(#{c2}, 0, 0)"
              data.expected_hit_count = if y * y + z * z < 1 then 4 else 0 end
            end
          end
        end
      end
    end
  end
end
