#pragma once

#include "utils.hpp"

class Analyzer
{
public:
    Analyzer(const boost::filesystem::path& file);

    const boost::filesystem::path m_header_file;
    const boost::filesystem::path m_source_file;

    bool parseCompareBothMethods() const;

private:
    std::string m_class_name;
    Utils::StringList_t m_header_methods;
    Utils::StringList_t m_source_methods;

    static std::string cleanMethodSignature(std::string line);
};
