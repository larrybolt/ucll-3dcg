require './shared.rb'


test_file 'math/quaternion' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "math/quaternion.h"

      using namespace math;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Quaternion] Rotation around #{axis} by #{angle} degrees of #{point}", "[Quaternion]")
        {
            Angle angle = #{angle}_degrees;
            Vector3D axis = Vector3D#{axis}.normalized();
            Quaternion quaternion = Quaternion::rotation(angle, axis);
            Point3D point#{point};
            Point3D expected#{expected};
            Point3D actual = quaternion.rotate(point);

            REQUIRE( actual == approx(expected) );
        }
      END
    end

    [-5, 0, 3].each do |a|
      [-4, 2, 8].each do |b|
        [-1, 0, 3].each do |c|
          test_case do |data|
            data.angle = 0
            data.axis = "(#{a}, #{b}, #{c})"
            data.point = "(#{b}, #{a}, #{c})"
            data.expected = data.point;
          end
        end
      end
    end

    [-5, 0, 3].each do |x|
      [-4, 0, 8].each do |y|
        [-1, 0, 3].each do |z|
          test_case do |data|
            data.angle = 180
            data.axis = "(1, 0, 0)"
            data.point = "(#{x}, #{y}, #{z})"
            data.expected = "(#{x}, #{-y}, #{-z})"
          end

          test_case do |data|
            data.angle = 90
            data.axis = "(1, 0, 0)"
            data.point = "(#{x}, #{y}, #{z})"
            data.expected = "(#{x}, #{-z}, #{y})"
          end

          test_case do |data|
            data.angle = -90
            data.axis = "(1, 0, 0)"
            data.point = "(#{x}, #{y}, #{z})"
            data.expected = "(#{x}, #{z}, #{-y})"
          end
          
          test_case do |data|
            data.angle = 180
            data.axis = "(0, 1, 0)"
            data.point = "(#{x}, #{y}, #{z})"
            data.expected = "(#{-x}, #{y}, #{-z})"
          end

          test_case do |data|
            data.angle = 90
            data.axis = "(0, 1, 0)"
            data.point = "(#{x}, #{y}, #{z})"
            data.expected = "(#{z}, #{y}, #{-x})"
          end

          test_case do |data|
            data.angle = -90
            data.axis = "(0, 1, 0)"
            data.point = "(#{x}, #{y}, #{z})"
            data.expected = "(#{-z}, #{y}, #{x})"
          end

          test_case do |data|
            data.angle = 180
            data.axis = "(0, 0, 1)"
            data.point = "(#{x}, #{y}, #{z})"
            data.expected = "(#{-x}, #{-y}, #{z})"
          end

          test_case do |data|
            data.angle = 90
            data.axis = "(0, 0, 1)"
            data.point = "(#{x}, #{y}, #{z})"
            data.expected = "(#{-y}, #{x}, #{z})"
          end

          test_case do |data|
            data.angle = -90
            data.axis = "(0, 0, 1)"
            data.point = "(#{x}, #{y}, #{z})"
            data.expected = "(#{y}, #{-x}, #{z})"
          end
        end
      end      
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Quaternion] Rotation around #{axis} by #{angle} degrees then by #{-angle} degrees of #{point} is no op", "[Quaternion]")
        {
            Angle angle = #{angle}_degrees;
            Vector3D axis = Vector3D#{axis}.normalized();
            Quaternion q1 = Quaternion::rotation(angle, axis);
            Quaternion q2 = Quaternion::rotation(-angle, axis);
            Point3D point#{point};
            Point3D expected = point;
            Point3D actual = q2.rotate(q1.rotate(point));

            REQUIRE( actual == approx(expected) );
        }
      END
    end

    [-2, 0, 5].each do |x|
      [-3, 0, 1].each do |y|
        [-7, 0, 6].each do |z|
          [-2, 0, 1].each do |vx|
            [-1, 3, 7].each do |vy|
              [-8, 0, 9].each do |vz|
                [10, 50, 90, 135, 217].each do |angle|
                  test_case do |data|
                    data.angle = angle
                    data.axis = "(#{vx}, #{vy}, #{vz})"
                    data.point = "(#{x}, #{y}, #{z})"
                  end
                end
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
        TEST_CASE("[Quaternion] Rotation around #{axis} then by inverted axis by #{angle} degrees of #{point} is no op", "[Quaternion]")
        {
            Angle angle = #{angle}_degrees;
            Vector3D axis = Vector3D#{axis}.normalized();
            Quaternion q1 = Quaternion::rotation(angle, axis);
            Quaternion q2 = Quaternion::rotation(angle, -axis);
            Point3D point#{point};
            Point3D expected = point;
            Point3D actual = q2.rotate(q1.rotate(point));

            REQUIRE( actual == approx(expected) );
        }
      END
    end

    [-2, 0, 5].each do |x|
      [-3, 0, 1].each do |y|
        [-7, 0, 6].each do |z|
          [-2, 0, 1].each do |vx|
            [-1, 3, 7].each do |vy|
              [-8, 0, 9].each do |vz|
                [10, 50, 90, 135, 217].each do |angle|
                  test_case do |data|
                    data.angle = angle
                    data.axis = "(#{vx}, #{vy}, #{vz})"
                    data.point = "(#{x}, #{y}, #{z})"
                  end
                end
              end
            end
          end
        end
      end
    end
  end
end
