#pragma once

#include "utils.hpp"

class HeaderParser
{
public:
    HeaderParser(const boost::filesystem::path& file);
    HeaderParser(Utils::StringList_t lines);

    ~HeaderParser() = default;

    std::pair<std::string, Utils::StringList_t> run();

    static std::string cleanUpMethodSignature(std::string line);

    Utils::StringList_t m_lines;
};
