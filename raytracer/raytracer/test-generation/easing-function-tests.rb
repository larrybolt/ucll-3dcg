require './shared.rb'


file_template = proc do
  <<-'END'
    #ifdef TEST_BUILD

    #include "Catch.h"
    #include "math/functions/easing-functions.h"
    #include "math/interval.h"
    #include "math/approx.h"

    using namespace math;
    using namespace math::functions::easing;


    <<<TESTS>>>

    #endif
  END
end


test_file 'math/functions/easing/linear' do
  template do
    instance_eval(&file_template)
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Linear] At #{x}", "[Linear]")
        {
          auto f = math::functions::easing::linear();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end

    (0..10).each do |t|
      x = t / 10.0
      
      test_case do |data|
        data.x = x
        data.y = x
      end
    end
  end
end

test_file 'math/functions/easing/quadratic/quadratic-in' do
  template do
    instance_eval(&file_template)
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[QuadraticIn] At #{x}", "[QuadraticIn]")
        {
          auto f = math::functions::easing::quadratic_in();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end

    [ [0, 0],
      [0.05, 0.0025],
      [0.1, 0.01],
      [0.15, 0.0225],
      [0.2, 0.04],
      [0.25, 0.0625],
      [0.3, 0.09],
      [0.35, 0.1225],
      [0.4, 0.16],
      [0.45, 0.2025],
      [0.5, 0.25],
      [0.55, 0.3025],
      [0.6, 0.36],
      [0.65, 0.4225],
      [0.7, 0.49],
      [0.75, 0.5625],
      [0.8, 0.64],
      [0.85, 0.7225],
      [0.9, 0.81],
      [0.95, 0.9025],
      [1, 1] ].each do |x, y|
      test_case do |data|
        data.x = x
        data.y = y
      end
    end
  end
end

test_file 'math/functions/easing/quadratic/quadratic-out' do
  template do
    instance_eval(&file_template)
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[QuadraticOut] At #{x}", "[QuadraticOut]")
        {
          auto f = math::functions::easing::quadratic_out();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end

    [ [0, 0],
      [0.05, 0.0975],
      [0.1, 0.19],
      [0.15, 0.2775],
      [0.2, 0.36],
      [0.25, 0.4375],
      [0.3, 0.51],
      [0.35, 0.5775],
      [0.4, 0.64],
      [0.45, 0.6975],
      [0.5, 0.75],
      [0.55, 0.7975],
      [0.6, 0.84],
      [0.65, 0.8775],
      [0.7, 0.91],
      [0.75, 0.9375],
      [0.8, 0.96],
      [0.85, 0.9775],
      [0.9, 0.99],
      [0.95, 0.9975],
      [1, 1] ].each do |x, y|
      test_case do |data|
        data.x = x
        data.y = y
      end
    end
  end
end

test_file 'math/functions/easing/quadratic/quadratic-inout' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[QuadraticInOut] At #{x}", "[QuadraticInOut]")
        {
          auto f = math::functions::easing::quadratic_inout();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end
    
    [ [0, 0],
      [0.05, 0.005],
      [0.1, 0.02],
      [0.15, 0.045],
      [0.2, 0.08],
      [0.25, 0.125],
      [0.3, 0.18],
      [0.35, 0.245],
      [0.4, 0.32],
      [0.45, 0.405],
      [0.5, 0.5],
      [0.55, 0.595],
      [0.6, 0.68],
      [0.65, 0.755],
      [0.7, 0.82],
      [0.75, 0.875],
      [0.8, 0.92],
      [0.85, 0.955],
      [0.9, 0.98],
      [0.95, 0.995],
      [1, 1] ].each do |x, y|
      test_case do |data|
        data.x = x
        data.y = y
      end
    end
  end
end

test_file 'math/functions/easing/cubic/cubic-in' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[CubicIn] At #{x}", "[CubicIn]")
        {
          auto f = math::functions::easing::cubic_in();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end
    
    [ [0, 0],
      [0.05, 0.000125],
      [0.1, 0.001],
      [0.15, 0.003375],
      [0.2, 0.008],
      [0.25, 0.015625],
      [0.3, 0.027],
      [0.35, 0.042875],
      [0.4, 0.064],
      [0.45, 0.091125],
      [0.5, 0.125],
      [0.55, 0.166375],
      [0.6, 0.216],
      [0.65, 0.274625],
      [0.7, 0.343],
      [0.75, 0.421875],
      [0.8, 0.512],
      [0.85, 0.614125],
      [0.9, 0.729],
      [0.95, 0.857375],
      [1, 1] ].each do |x, y|
      test_case do |data|
        data.x = x
        data.y = y
      end
    end
  end
end

test_file 'math/functions/easing/cubic/cubic-out' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[CubicOut] At #{x}", "[CubicOut]")
        {
          auto f = math::functions::easing::cubic_out();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end
    
    [ [0, 0],
      [0.05, 0.142625],
      [0.1, 0.271],
      [0.15, 0.385875],
      [0.2, 0.488],
      [0.25, 0.578125],
      [0.3, 0.657],
      [0.35, 0.725375],
      [0.4, 0.784],
      [0.45, 0.833625],
      [0.5, 0.875],
      [0.55, 0.908875],
      [0.6, 0.936],
      [0.65, 0.957125],
      [0.7, 0.973],
      [0.75, 0.984375],
      [0.8, 0.992],
      [0.85, 0.996625],
      [0.9, 0.999],
      [0.95, 0.999875],
      [1, 1] ].each do |x, y|
      test_case do |data|
        data.x = x
        data.y = y
      end
    end
  end
end

test_file 'math/functions/easing/cubic/cubic-inout' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[CubicInOut] At #{x}", "[CubicInOut]")
        {
          auto f = math::functions::easing::cubic_inout();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end
    
    [ [0, 0],
      [0.05, 0.0005],
      [0.1, 0.004],
      [0.15, 0.0135],
      [0.2, 0.032],
      [0.25, 0.0625],
      [0.3, 0.108],
      [0.35, 0.1715],
      [0.4, 0.256],
      [0.45, 0.3645],
      [0.5, 0.5],
      [0.55, 0.6355],
      [0.6, 0.744],
      [0.65, 0.8285],
      [0.7, 0.892],
      [0.75, 0.9375],
      [0.8, 0.968],
      [0.85, 0.9865],
      [0.9, 0.996],
      [0.95, 0.9995],
      [1, 1] ].each do |x, y|
      test_case do |data|
        data.x = x
        data.y = y
      end
    end
  end
end

test_file 'math/functions/easing/quintic/quintic-in' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[QuinticIn] At #{x}", "[QuinticIn]")
        {
          auto f = math::functions::easing::quintic_in();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end
    
    [ [0, 0],
      [0.05, 3.125e-07],
      [0.1, 1e-05],
      [0.15, 7.59375e-05],
      [0.2, 0.00032],
      [0.25, 0.000976563],
      [0.3, 0.00243],
      [0.35, 0.00525219],
      [0.4, 0.01024],
      [0.45, 0.0184528],
      [0.5, 0.03125],
      [0.55, 0.0503284],
      [0.6, 0.07776],
      [0.65, 0.116029],
      [0.7, 0.16807],
      [0.75, 0.237305],
      [0.8, 0.32768],
      [0.85, 0.443705],
      [0.9, 0.59049],
      [0.95, 0.773781],
      [1, 1] ].each do |x, y|
      test_case do |data|
        data.x = x
        data.y = y
      end
    end
  end
end

test_file 'math/functions/easing/quintic/quintic-out' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[QuinticOut] At #{x}", "[QuinticOut]")
        {
          auto f = math::functions::easing::quintic_out();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end
    
    [ [0, 0],
      [0.05, 0.226219],
      [0.1, 0.40951],
      [0.15, 0.556295],
      [0.2, 0.67232],
      [0.25, 0.762695],
      [0.3, 0.83193],
      [0.35, 0.883971],
      [0.4, 0.92224],
      [0.45, 0.949672],
      [0.5, 0.96875],
      [0.55, 0.981547],
      [0.6, 0.98976],
      [0.65, 0.994748],
      [0.7, 0.99757],
      [0.75, 0.999023],
      [0.8, 0.99968],
      [0.85, 0.999924],
      [0.9, 0.99999],
      [0.95, 1],
      [1, 1] ].each do |x, y|
      test_case do |data|
        data.x = x
        data.y = y
      end
    end
  end
end

test_file 'math/functions/easing/quintic/quintic-inout' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[QuinticInOut] At #{x}", "[QuinticInOut]")
        {
          auto f = math::functions::easing::quintic_inout();

          CHECK(f(#{x}) == Approx(#{y}));
        }
      END
    end
    
    [ [0, 0],
      [0.05, 5e-06],
      [0.1, 0.00016],
      [0.15, 0.001215],
      [0.2, 0.00512],
      [0.25, 0.015625],
      [0.3, 0.03888],
      [0.35, 0.084035],
      [0.4, 0.16384],
      [0.45, 0.295245],
      [0.5, 0.5],
      [0.55, 0.704755],
      [0.6, 0.83616],
      [0.65, 0.915965],
      [0.7, 0.96112],
      [0.75, 0.984375],
      [0.8, 0.99488],
      [0.85, 0.998785],
      [0.9, 0.99984],
      [0.95, 0.999995],
      [1, 1] ].each do |x, y|
      test_case do |data|
        data.x = x
        data.y = y
      end
    end
  end
end

test_file 'math/functions/easing/stretch/stretch-in-time' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[Stretch] Stretch in time to [#{a}, #{b}]", "[Stretch]")
        {
          auto range = interval<double>(#{a}, #{b});
          auto f = stretch_in_time( math::functions::easing::linear(), range );

          for ( int i = 0; i <= 20; ++i )
          {
              double x = i / 20.0;
              double t = range.from_relative(x);

              CHECK(f(t) == Approx(x));
          }
        }
      END
    end
    
    (-2..2).each do |a|
      (1..4).each do |delta|
        test_case do |data|
          data.a = a
          data.b = a + delta
        end
      end
    end
  end
end

test_file 'math/functions/easing/stretch/stretch-in-space' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[Stretch] Stretch in space to [#{a}, #{b}]", "[Stretch]")
        {
          auto range = interval<double>(#{a}, #{b});
          auto f = stretch_in_space( math::functions::easing::linear(), range );

          for ( int i = 0; i <= 20; ++i )
          {
              double x = i / 20.0;
              double t = range.from_relative(x);

              CHECK(f(x) == Approx(t));
          }
        }
      END
    end
    
    (-2..2).each do |a|
      (1..4).each do |delta|
        test_case do |data|
          data.a = a
          data.b = a + delta
        end
      end
    end
  end
end

test_file 'math/functions/easing/stretch/stretch' do
  template do
    instance_eval(&file_template)
  end
  
  test_suite do
    template do
      <<-END
        TEST_CASE("[Stretch] Stretch in time [#{a}, #{b}] and space [#{c}, #{d}]", "[Stretch]")
        {
          auto time_range = interval<double>(#{a}, #{b});
          auto space_range = interval<double>(#{c}, #{d});
          auto f = stretch( math::functions::easing::linear(), time_range, space_range );

          for ( int i = 0; i <= 20; ++i )
          {
              double x = i / 20.0;

              double time = time_range.from_relative(x);
              double space = space_range.from_relative(x);

              INFO( "x = " << x << ", time = " << time << ", space = " << space );

              CHECK(f(time) == Approx(space));
          }
        }
      END
    end
    
    (-2..2).each do |a|
      (1..4).each do |delta_ab|
        (-2..2).each do |c|
          (1..4).each do |delta_cd|
            test_case do |data|
              data.a = a
              data.b = a + delta_ab
              data.c = c
              data.d = c + delta_cd
            end
          end
        end
      end
    end
  end
end
