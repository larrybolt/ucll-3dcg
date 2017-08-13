require './shared.rb'


test_file 'math/interval' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "math/interval.h"
      #include "math/angle.h"
      #include "math/point.h"
      #include "math/approx.h"

      using namespace math;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Interval] interval(#{from}, #{to}).from_relative(#{t})", "[Interval]")
        {
            auto i = interval(#{from}, #{to});
            auto t = #{t};
            auto actual = i.from_relative(t);
            auto expected = #{x};

            REQUIRE(actual == approx(expected));
        }

        TEST_CASE("[Interval] interval(#{from}, #{to}).to_relative(#{x})", "[Interval]")
        {
            auto i = interval(#{from}, #{to});
            auto x = #{x};
            auto actual = i.to_relative(x);
            auto expected = #{t};

            REQUIRE(actual == approx(expected));
        }
      END
    end

    test_case do |data|
      data.from = '0.0'
      data.to = '1.0'
      data.t = '0.0'
      data.x = '0.0'
    end

    test_case do |data|
      data.from = '0.0'
      data.to = '1.0'
      data.t = '1.0'
      data.x = '1.0'
    end

    test_case do |data|
      data.from = '0.0'
      data.to = '1.0'
      data.t = '0.5'
      data.x = '0.5'
    end

    test_case do |data|
      data.from = '0.0'
      data.to = '2.0'
      data.t = '0.0'
      data.x = '0.0'
    end

    test_case do |data|
      data.from = '0.0'
      data.to = '2.0'
      data.t = '1.0'
      data.x = '2.0'
    end

    test_case do |data|
      data.from = '0.0'
      data.to = '2.0'
      data.t = '0.5'
      data.x = '1.0'
    end

    test_case do |data|
      data.from = '1.0'
      data.to = '3.0'
      data.t = '0.0'
      data.x = '1.0'
    end

    test_case do |data|
      data.from = '1.0'
      data.to = '3.0'
      data.t = '1.0'
      data.x = '3.0'
    end

    test_case do |data|
      data.from = '1.0'
      data.to = '3.0'
      data.t = '0.5'
      data.x = '2.0'
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Interval] #{i1}.intersect(#{i2})", "[Interval]")
        {
            auto i1 = #{i1};
            auto i2 = #{i2};
            auto expected = #{expected};
            auto actual = i1.intersect(i2);

            REQUIRE(actual.lower == approx(expected.lower));
            REQUIRE(actual.upper == approx(expected.upper));
        }
      END
    end

    def interval(from, to)
      "interval(#{from}.0, #{to}.0)"
    end

    def empty_interval
      "Interval<double>::empty()"
    end

    def infinite_interval
      "Interval<double>::infinite()"
    end

    test_case do |data|
      data.i1 = empty_interval
      data.i2 = empty_interval
      data.expected = empty_interval
    end

    test_case do |data|
      data.i1 = empty_interval
      data.i2 = interval(0, 1)
      data.expected = empty_interval
    end

    test_case do |data|
      data.i1 = empty_interval
      data.i2 = interval(-1, 1)
      data.expected = empty_interval
    end

    test_case do |data|
      data.i1 = interval(0, 1)
      data.i2 = empty_interval
      data.expected = empty_interval
    end

    test_case do |data|
      data.i1 = interval(0, 5)
      data.i2 = empty_interval
      data.expected = empty_interval
    end

    test_case do |data|
      data.i1 = infinite_interval
      data.i2 = interval(0, 1)
      data.expected = interval(0, 1)
    end

    test_case do |data|
      data.i1 = infinite_interval
      data.i2 = infinite_interval
      data.expected = infinite_interval
    end

    test_case do |data|
      data.i1 = infinite_interval
      data.i2 = empty_interval
      data.expected = empty_interval
    end

    test_case do |data|
      data.i1 = empty_interval
      data.i2 = infinite_interval
      data.expected = empty_interval
    end
        
    test_case do |data|
      data.i1 = interval(0, 1)
      data.i2 = interval(0, 1)
      data.expected = interval(0, 1)
    end

    test_case do |data|
      data.i1 = interval(0, 1)
      data.i2 = interval(0, 2)
      data.expected = interval(0, 1)
    end

    test_case do |data|
      data.i1 = interval(0, 1)
      data.i2 = interval(-1, 2)
      data.expected = interval(0, 1)
    end
    
    test_case do |data|
      data.i1 = interval(-1, 1)
      data.i2 = interval(0, 1)
      data.expected = interval(0, 1)
    end

    test_case do |data|
      data.i1 = interval(0, 2)
      data.i2 = interval(0, 1)
      data.expected = interval(0, 1)
    end

    test_case do |data|
      data.i1 = interval(0, 2)
      data.i2 = interval(0, 3)
      data.expected = interval(0, 2)
    end

    test_case do |data|
      data.i1 = interval(-1, 2)
      data.i2 = interval(0, 3)
      data.expected = interval(0, 2)
    end

    test_case do |data|
      data.i1 = interval(-1, 2)
      data.i2 = interval(-2, 1)
      data.expected = interval(-1, 1)
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Interval] #{i1}.merge(#{i2})", "[Interval]")
        {
            auto i1 = #{i1};
            auto i2 = #{i2};
            auto expected = #{expected};
            auto actual = i1.merge(i2);

            REQUIRE(actual.lower == approx(expected.lower));
            REQUIRE(actual.upper == approx(expected.upper));
        }
      END
    end

    def interval(from, to)
      "interval(#{from}.0, #{to}.0)"
    end

    def empty_interval
      "Interval<double>::empty()"
    end

    def infinite_interval
      "Interval<double>::infinite()"
    end

    test_case do |data|
      data.i1 = interval(0, 1)
      data.i2 = interval(0, 1)
      data.expected = interval(0, 1)
    end

    test_case do |data|
      data.i1 = interval(0, 1)
      data.i2 = interval(1, 2)
      data.expected = interval(0, 2)
    end

    test_case do |data|
      data.i1 = interval(0, 1)
      data.i2 = interval(2, 3)
      data.expected = interval(0, 3)
    end

    test_case do |data|
      data.i1 = empty_interval
      data.i2 = empty_interval
      data.expected = empty_interval
    end
    
    test_case do |data|
      data.i1 = empty_interval
      data.i2 = interval(0, 1)
      data.expected = interval(0, 1)
    end

    test_case do |data|
      data.i1 = interval(0, 1)
      data.i2 = empty_interval
      data.expected = interval(0, 1)
    end

    test_case do |data|
      data.i1 = infinite_interval
      data.i2 = interval(0, 1)
      data.expected = infinite_interval
    end

    test_case do |data|
      data.i1 = interval(0, 1)
      data.i2 = infinite_interval
      data.expected = infinite_interval
    end
    
    test_case do |data|
      data.i1 = infinite_interval
      data.i2 = empty_interval
      data.expected = infinite_interval
    end

    test_case do |data|
      data.i1 = empty_interval
      data.i2 = infinite_interval
      data.expected = infinite_interval
    end
  end
end
