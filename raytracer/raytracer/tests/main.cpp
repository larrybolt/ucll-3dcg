#ifdef TEST_BUILD
#define CATCH_CONFIG_RUNNER
#include "Catch.h"
#include "easylogging++.h"
#include "logging.h"
#include "performance/performance.h"


int main(int argc, char* const argv[])
{
    logging::configure();

    Catch::ConfigData data;
    // data.abortAfter = 5;  // Makes the tests stop running after 5 failures
    
    Catch::Session session;
    session.useConfigData(data);
    auto result = session.run(argc, argv);

    performance::print_statistics(std::cerr);

    return result;
}

#endif
