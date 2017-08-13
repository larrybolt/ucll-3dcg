#include "logging.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

void logging::configure()
{
    el::Configurations configuration;

    configuration.setToDefault();
    configuration.set(el::Level::Info, el::ConfigurationType::Enabled, "true");
    el::Loggers::reconfigureLogger("performance", configuration);

    configuration.setToDefault();
    configuration.set(el::Level::Info, el::ConfigurationType::Enabled, "true");
    configuration.set(el::Level::Debug, el::ConfigurationType::Format, "[%level] (%fbase:%line) %msg");
    el::Loggers::reconfigureLogger("default", configuration);

    configuration.setToDefault();
    configuration.set(el::Level::Info, el::ConfigurationType::Enabled, "false");
    el::Loggers::reconfigureLogger("studio", configuration);
}

void logging::quiet()
{
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Enabled, "false");

    //el::Configurations configuration;
    //configuration.setToDefault();
    //configuration.set(el::Level::Error, el::ConfigurationType::Enabled, "true");
    //el::Loggers::reconfigureLogger("default", configuration);
}

void logging::enable(const std::string& channel)
{
    el::Configurations configuration;
    configuration.setToDefault();
    configuration.set(el::Level::Info, el::ConfigurationType::Enabled, "true");
    configuration.set(el::Level::Info, el::ConfigurationType::Format, "%msg");
    el::Loggers::reconfigureLogger("studio", configuration);
}
