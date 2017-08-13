#ifndef TEST_BUILD

#include "easylogging++.h"
#include "version.h"
#include "command-line-parser.h"
#include "logging.h"
#include "demos/demos.h"
#include "pipeline/pipelines.h"
#include "util/beep.h"
#include "scripting/scripting.h"
#include "performance/performance.h"
#include <assert.h>

using namespace raytracer;


namespace
{
    void render_script(const std::string& filename)
    {
        TIMED_SCOPE(timer, "Rendering script");

#       ifdef EXCLUDE_SCRIPTING
        LOG(ERROR) << "Cannot run script - scripting was excluded";
        abort();
#       endif

        if (filename != "-")
        {
            LOG(INFO) << "Rendering " << filename;

            raytracer::scripting::run_script(filename);
        }
        else
        {
            LOG(INFO) << "Rendering script from STDIN";

            std::string script;

            while (!std::cin.eof())
            {
                std::string line;
                std::getline(std::cin, line);
                script += line + "\n";
            }

            raytracer::scripting::run(script);
        }
    }

    void quiet()
    {
        logging::quiet();
    }

    void show_version()
    {
        LOG(INFO) << "Build " << BUILD_NUMBER << std::endl;
    }

    void emit_beep()
    {
        ::beep();
    }

    void print_statistics()
    {
        performance::print_statistics(std::cerr);
    }

    void enable_3dstudio_output()
    {
        logging::enable("studio");

        LOG(INFO) << "Activated 3d studio mode";
    }
}

void process_command_line_arguments(int argc, char** argv)
{
    CommandLineParser parser;

    parser.register_processor("-s", render_script);
    parser.register_processor("--quiet", quiet);
    parser.register_processor("--version", show_version);
    parser.register_processor("--beep", emit_beep);
    parser.register_processor("--statistics", print_statistics);
    parser.register_processor("--studio", enable_3dstudio_output);

    parser.process(argc, argv);

    LOG(INFO) << "Terminated successfully";
}

int main(int argc, char** argv)
{
    TIMED_FUNC(timer);

    logging::configure();
    process_command_line_arguments(argc, argv);

    // demos::basic_sample(pipeline::wif("test.wif"));
}

#endif
