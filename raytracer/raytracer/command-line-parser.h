#pragma once

#include <functional>
#include <string>
#include <list>
#include <map>


class CommandLineParser
{
public:
    void register_processor(const std::string& prefix, std::function<void()> processor);
    void register_processor(const std::string& prefix, std::function<void(const std::string&)> processor);
    
    void process(int argc, char** argv) const;

private:
    void register_processor(const std::string& prefix, std::function<void(std::list<std::string>&)>);
    void process(std::list<std::string>&) const;
    bool is_prefix_in_use(const std::string& prefix) const;

    std::map<std::string, std::function<void(std::list<std::string>&)>> m_map;
};
