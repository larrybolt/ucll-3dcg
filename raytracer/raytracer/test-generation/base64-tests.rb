require './shared.rb'
require 'base64'


test_file 'util/base64' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "util/base64.h"


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      expected = Base64.encode64(data.pack("C" * data.size)).gsub(/\s+/, '')
      
      <<-END
        TEST_CASE("[Base64] Encoding #{data.map(&:to_s).join(' ')}", "[Base64]")
        {
            Base64 base64;
            std::vector<uint8_t> data = { #{data.map(&:to_s).join(', ')} };
            
            for ( auto datum : data )
            {
                base64.feed(datum);
            }

            base64.close();
            auto actual = base64.extract();
            auto expected = "#{expected}";

            REQUIRE( expected == actual );
        }
      END
    end

    (0..255).each do |datum|
      test_case do |data|
        data.data = [ datum ]
      end
    end

    (2..10).each do |n|
      test_case do |data|
        data.data = [ 1 ] * n
      end
    end

    test_case do |data|
      data.data = [ 77, 97, 110 ]
    end
  end
end
