#pragma once

#include "utils.hpp"

namespace CommonParsing
{

    void removeUselessLines(Utils::StringList_t& lines);

    std::string findClassName(const Utils::StringList_t& lines);

    Utils::StringList_t fuseSplittedLines(const Utils::StringList_t& lines);

    std::string cleanUpClassName(std::string line);
}
