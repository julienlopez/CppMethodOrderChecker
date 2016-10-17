#pragma once

#include "utils.hpp"

class SourceParser
{
public:
    SourceParser(std::string class_name, const boost::filesystem::path& file);

    SourceParser(std::string class_name, Utils::StringList_t lines);

    ~SourceParser() = default;

    Utils::StringList_t run();

private:
    const std::string m_class_name;
    Utils::StringList_t m_lines;

    std::string cleanUpMethodSignature(std::string line) const;

    std::string removeClassPrefix(std::string line) const;

    static std::string removeInitializationList(std::string line);

    static std::string removeDefault(std::string line);
};
