require './shared.rb'


file_template = <<'END'
  #ifdef TEST_BUILD

  #include "Catch.h"
  #include "math/matrix.h"
  #include "math/transformation-matrices.h"

  using namespace math;
  using namespace math::transformation_matrices;


  <<<TESTS>>>

  #endif
END


equal_transformation_template = proc do
  <<-END
    TEST_CASE("[Matrix] Matrix transformation #{first} equals #{second}", "[Matrix]")
    {
        auto a = #{first};
        auto b = #{second};

        REQUIRE( a == approx(b) );
    }
  END
end

transformation_template = proc do
  <<-END
    TEST_CASE("[Matrix] Matrix multiplication of #{first} and #{second} should give #{expected}", "[Matrix]")
    {
        auto a = #{first};
        auto b = #{second};
        auto actual = a * b;
        auto expected = #{expected};

        REQUIRE( actual == approx(expected) );
    }
  END
end

test_file 'math/matrix/translation2d' do
  template do
    file_template
  end

  test_suite do
    template do
      instance_eval(&equal_transformation_template)
    end

    test_case do |data|
      data.first = 'translation(Vector2D(0,0))'
      data.second = 'identity<3>()'
    end
  end

  test_suite do
    template do
      instance_eval(&transformation_template)
    end

    [1, 5].each do |delta|
      test_case do |data|
        data.first = "translation(Vector2D(#{delta}, 0))"
        data.second = "translation(Vector2D(-#{delta}, 0))"
        data.expected = "identity<3>()"
      end

      test_case do |data|
        data.first = "translation(Vector2D(0, #{delta}))"
        data.second = "translation(Vector2D(0, -#{delta}))"
        data.expected = "identity<3>()"
      end
    end

    [-1,0,3].each do |dx1|
      [-2,0,1].each do |dy1|
        [-5,0,4].each do |dx2|
          [-1,0,1].each do |dy2|
            test_case do |data|
              data.first = "translation(Vector2D(#{dx1}, #{dy1}))"
              data.second = "translation(Vector2D(#{dx2}, #{dy2}))"
              data.expected = "translation(Vector2D(#{dx1+dx2}, #{dy1+dy2}))"
            end
          end
        end
      end
    end

    [-2,0,5].each do |x|
      [-1,0,7].each do |y|
        [-8,0,1].each do |dx|
          [-5,0,4].each do |dy|
            test_case do |data|
              data.first = "translation(Vector2D(#{dx}, #{dy}))"
              data.second = "Vector2D(#{x}, #{y})"
              data.expected = "Vector2D(#{x}, #{y})"
            end

            test_case do |data|
              data.first = "translation(Vector2D(#{dx}, #{dy}))"
              data.second = "Point2D(#{x}, #{y})"
              data.expected = "Point2D(#{x + dx}, #{y + dy})"
            end
          end
        end
      end
    end
  end
end

test_file 'math/matrix/translation3d' do
  template do
    file_template
  end

  test_suite do
    template do
      instance_eval(&equal_transformation_template)
    end

    test_case do |data|
      data.first = 'translation(Vector3D(0,0,0))'
      data.second = 'identity<4>()'
    end
  end

  test_suite do
    template do
      instance_eval(&transformation_template)
    end

    [1, 4].each do |delta|
      test_case do |data|
        data.first = "translation(Vector3D(#{delta},0,0))"
        data.second = "translation(Vector3D(#{-delta},0,0))"
        data.expected = "identity<4>()"
      end

      test_case do |data|
        data.first = "translation(Vector3D(0,#{delta},0))"
        data.second = "translation(Vector3D(0,#{-delta},0))"
        data.expected = "identity<4>()"
      end

      test_case do |data|
        data.first = "translation(Vector3D(0,0,#{delta}))"
        data.second = "translation(Vector3D(0,0,#{-delta}))"
        data.expected = "identity<4>()"
      end
    end

    [-1,0,3].each do |a|
      [-2,0,5].each do |b|
        [-8,0,3].each do |c|
          test_case do |data|
            data.first = "translation(Vector3D(#{a},#{b},#{c}))"
            data.second = "translation(Vector3D(#{b},#{c},#{a}))"
            data.expected = "translation(Vector3D(#{a+b},#{b+c},#{c+a}))"
          end

          test_case do |data|
            data.first = "translation(Vector3D(#{a},#{b},#{c}))"
            data.second = "Vector3D(#{c},#{a},#{b})"
            data.expected = "Vector3D(#{c},#{a},#{b})"
          end
          
          test_case do |data|
            data.first = "translation(Vector3D(#{a},#{b},#{c}))"
            data.second = "Point3D(#{c},#{a},#{b})"
            data.expected = "Point3D(#{a+c},#{b+a},#{c+b})"
          end
        end
      end
    end
  end
end

test_file 'math/matrix/scaling2d' do
  template do
    file_template
  end

  test_suite do
    template do
      instance_eval(&equal_transformation_template)
    end

    test_case do |data|
      data.first = 'scaling(1,1)'
      data.second = 'identity<3>()'
    end
  end

  test_suite do
    template do
      instance_eval(&transformation_template)
    end

    [-1, 0.5, 1, 2].each do |sx1|
      [-1, 0.5, 1, 2].each do |sy1|
        [-1, 0.5, 1, 2].each do |sx2|
          [-1, 0.5, 1, 2].each do |sy2|
            test_case do |data|
              data.first = "scaling(#{sx1}, #{sy1})"
              data.second = "scaling(#{sx2}, #{sy2})"
              data.expected = "scaling(#{sx1 * sx2}, #{sy1 * sy2})"
            end
          end
        end
      end
    end

    [-1, 1, 2].each do |sx|
      [-1, 1, 2].each do |sy|
        test_case do |data|
          data.first = "identity<3>()"
          data.second = "scaling(#{sx}, #{sy})"
          data.expected = "scaling(#{sx}, #{sy})"
        end
      end
    end

    [-2,0,5].each do |x|
      [-1,0,7].each do |y|
        [-8,0,1].each do |sx|
          [-5,0,4].each do |sy|
            test_case do |data|
              data.first = "scaling(#{sx}, #{sy})"
              data.second = "Vector2D(#{x}, #{y})"
              data.expected = "Vector2D(#{sx * x}, #{sy * y})"
            end

            test_case do |data|
              data.first = "scaling(#{sx}, #{sy})"
              data.second = "Point2D(#{x}, #{y})"
              data.expected = "Point2D(#{sx * x}, #{sy * y})"
            end
          end
        end
      end
    end
  end
end

test_file 'math/matrix/scaling3d' do
  template do
    file_template
  end

  test_suite do
    template do
      instance_eval(&equal_transformation_template)
    end

    test_case do |data|
      data.first = 'scaling(1,1,1)'
      data.second = 'identity<4>()'
    end
  end

  test_suite do
    template do
      instance_eval(&transformation_template)
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'scaling(2, 1, 1)'
      data.expected = 'scaling(2, 1, 1)'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'scaling(1, 3, 1)'
      data.expected = 'scaling(1, 3, 1)'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'scaling(1, 1, 4)'
      data.expected = 'scaling(1, 1, 4)'
    end

    [-1, 0.5, 1, 2].each do |sx1|
      [-1, 0.5, 1, 2].each do |sy1|
        [-1, 0.5, 1, 2].each do |sz1|
          [-1, 0.5, 1, 2].each do |sx2|
            [-1, 0.5, 1, 2].each do |sy2|
              [-1, 0.5, 1, 2].each do |sz2|
                test_case do |data|
                  data.first = "scaling(#{sx1}, #{sy1}, #{sz1})"
                  data.second = "scaling(#{sx2}, #{sy2}, #{sz2})"
                  data.expected = "scaling(#{sx1 * sx2}, #{sy1 * sy2}, #{sz1 * sz2})"
                end
              end
            end
          end
        end
      end
    end

    [-1,0,3].each do |a|
      [-2,0,5].each do |b|
        [-8,0,3].each do |c|
          test_case do |data|
            data.first = "scaling(#{a}, #{b}, #{c})"
            data.second = "Point3D(#{b}, #{c}, #{a})"
            data.expected = "Point3D(#{a*b}, #{b*c}, #{a*c})"
          end

          test_case do |data|
            data.first = "scaling(#{a}, #{b}, #{c})"
            data.second = "Vector3D(#{b}, #{c}, #{a})"
            data.expected = "Vector3D(#{a*b}, #{b*c}, #{a*c})"
          end
        end
      end
    end
  end
end

test_file 'math/matrix/rotation2d' do
  template do
    file_template
  end

  test_suite do
    template do
      instance_eval(&equal_transformation_template)
    end

    test_case do |data|
      data.first = 'rotation(0_degrees)'
      data.second = 'identity<3>()'
    end

    test_case do |data|
      data.first = 'rotation(0_degrees)'
      data.second = 'rotation(360_degrees)'
    end

    test_case do |data|
      data.first = 'rotation(-90_degrees)'
      data.second = 'rotation(270_degrees)'
    end

    test_case do |data|
      data.first = 'rotation(-180_degrees)'
      data.second = 'rotation(180_degrees)'
    end
  end

  test_suite do
    template do
      instance_eval(&transformation_template)
    end

    [0, 10, 90, 180, 270].each do |angle|
      test_case do |data|
        data.first = "identity<3>()"
        data.second = "rotation(#{angle}_degrees)"
        data.expected = "rotation(#{angle}_degrees)"
      end
    end

    [0, -10, 50, 90, 180, 270, 360, 720].each do |angle1|
      [0, -10, 50, 90, 180, 270, 360, 720].each do |angle2|
        test_case do |data|
          data.first = "rotation(#{angle1}_degrees)"
          data.second = "rotation(#{angle2}_degrees)"
          data.expected = "rotation(#{angle1 + angle2}_degrees)"
        end
      end
    end

    [-2,0,4].each do |x|
      [-3,0,7].each do |y|
        test_case do |data|
          data.first = "rotation(180_degrees)"
          data.second = "Point2D(#{x}, #{y})"
          data.expected = "Point2D(#{-x}, #{-y})"
        end

        test_case do |data|
          data.first = "rotation(180_degrees)"
          data.second = "Vector2D(#{x}, #{y})"
          data.expected = "Vector2D(#{-x}, #{-y})"
        end

        test_case do |data|
          data.first = "rotation(90_degrees)"
          data.second = "Point2D(#{x}, #{y})"
          data.expected = "Point2D(#{-y}, #{x})"
        end

        test_case do |data|
          data.first = "rotation(90_degrees)"
          data.second = "Vector2D(#{x}, #{y})"
          data.expected = "Vector2D(#{-y}, #{x})"
        end

        test_case do |data|
          data.first = "rotation(-90_degrees)"
          data.second = "Point2D(#{x}, #{y})"
          data.expected = "Point2D(#{y}, #{-x})"
        end

        test_case do |data|
          data.first = "rotation(-90_degrees)"
          data.second = "Vector2D(#{x}, #{y})"
          data.expected = "Vector2D(#{y}, #{-x})"
        end
      end
    end
  end
end

test_file 'math/matrix/rotation3d' do
  template do
    file_template
  end

  test_suite do
    template do
      instance_eval(&equal_transformation_template)
    end

    test_case do |data|
      data.first = 'rotation_around_x(0_degrees)'
      data.second = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'rotation_around_y(0_degrees)'
      data.second = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'rotation_around_z(0_degrees)'
      data.second = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'rotation_around_x(0_degrees)'
      data.second = 'rotation_around_x(360_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(-90_degrees)'
      data.second = 'rotation_around_x(270_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(-180_degrees)'
      data.second = 'rotation_around_x(180_degrees)'
    end
  end

  test_suite do
    template do
      instance_eval(&transformation_template)
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'rotation_around_x(40_degrees)'
      data.expected = 'rotation_around_x(40_degrees)'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'rotation_around_y(10_degrees)'
      data.expected = 'rotation_around_y(10_degrees)'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'rotation_around_z(250_degrees)'
      data.expected = 'rotation_around_z(250_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(10_degrees)'
      data.second = 'rotation_around_x(10_degrees)'
      data.expected = 'rotation_around_x(20_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(10_degrees)'
      data.second = 'rotation_around_x(-10_degrees)'
      data.expected = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'rotation_around_x(10_degrees)'
      data.second = 'rotation_around_x(20_degrees)'
      data.expected = 'rotation_around_x(30_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(10_degrees)'
      data.second = 'rotation_around_y(20_degrees)'
      data.expected = 'rotation_around_y(30_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(10_degrees)'
      data.second = 'rotation_around_z(20_degrees)'
      data.expected = 'rotation_around_z(30_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(180_degrees)'
      data.second = 'Point3D(2,2,2)'
      data.expected = 'Point3D(2,-2,-2)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(180_degrees)'
      data.second = 'Point3D(2,2,2)'
      data.expected = 'Point3D(-2,2,-2)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(180_degrees)'
      data.second = 'Point3D(2,2,2)'
      data.expected = 'Point3D(-2,-2,2)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(180_degrees)'
      data.second = 'Vector3D(2,2,2)'
      data.expected = 'Vector3D(2,-2,-2)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(180_degrees)'
      data.second = 'Vector3D(2,2,2)'
      data.expected = 'Vector3D(-2,2,-2)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(180_degrees)'
      data.second = 'Vector3D(2,2,2)'
      data.expected = 'Vector3D(-2,-2,2)'
    end
    
    test_case do |data|
      data.first = 'rotation_around_x(90_degrees)'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(90_degrees)'
      data.second = 'Point3D(1,0,0)'
      data.expected = 'Point3D(1,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(90_degrees)'
      data.second = 'Point3D(0,1,0)'
      data.expected = 'Point3D(0,0,1)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(90_degrees)'
      data.second = 'Point3D(0,0,1)'
      data.expected = 'Point3D(0,-1,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(0,1,0)'
      data.expected = 'Point3D(0,1,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(1,0,0)'
      data.expected = 'Point3D(0,0,-1)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(0,0,-1)'
      data.expected = 'Point3D(-1,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(-1,0,0)'
      data.expected = 'Point3D(0,0,1)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(90_degrees)'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(90_degrees)'
      data.second = 'Point3D(0,0,1)'
      data.expected = 'Point3D(0,0,1)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(90_degrees)'
      data.second = 'Point3D(1,0,0)'
      data.expected = 'Point3D(0,1,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(90_degrees)'
      data.second = 'Point3D(0,1,0)'
      data.expected = 'Point3D(-1,0,0)'
    end
  end
end

test_file 'math/matrix/mixed' do
  template do
    file_template
  end

  test_suite do
    template do
      instance_eval(&equal_transformation_template)
    end

    test_case do |data|
      data.first = 'identity<3>()'
      data.second = 'identity<3>()'
    end

    test_case do |data|
      data.first = 'scaling(-1,-1)'
      data.second = 'rotation(180_degrees)'
    end

    test_case do |data|
      data.first = 'scaling(-1,1,-1)'
      data.second = 'rotation_around_y(180_degrees)'
    end

    test_case do |data|
      data.first = 'scaling(-1,-1,1)'
      data.second = 'rotation_around_z(180_degrees)'
    end

    test_case do |data|
      data.first = 'scaling(1,-1,-1)'
      data.second = 'rotation_around_x(180_degrees)'
    end
  end

  test_suite do
    template do
      instance_eval(&transformation_template)
    end

    test_case do |data|
      data.first = 'identity<3>()'
      data.second = 'identity<3>()'
      data.expected = 'identity<3>()'
    end
    
    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'identity<4>()'
      data.expected = 'identity<4>()'
    end
  end
end
