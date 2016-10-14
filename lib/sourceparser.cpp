#include "sourceparser.hpp"

#include "commonparsing.hpp"

#include <iostream>

SourceParser::SourceParser(std::string class_name, const boost::filesystem::path& file)
    : SourceParser(class_name, Utils::loadFileAsStringList(file))
{
}

SourceParser::SourceParser(std::string class_name, Utils::StringList_t lines)
    : m_class_name(std::move(class_name))
    , m_lines(std::move(lines))
{
}

Utils::StringList_t SourceParser::run()
{
    std::transform(begin(m_lines), end(m_lines), begin(m_lines), &Utils::trim);
    m_lines = CommonParsing::fuseSplittedLines(m_lines);
    auto it = std::remove_if(begin(m_lines), end(m_lines),
                             [this](const std::string& line) { return !Utils::contains(line, m_class_name + "::"); });
    m_lines.erase(it, end(m_lines));
    return m_lines;
}

std::string SourceParser::cleanUpMethodSignature(std::string line) const
{
    line = Utils::trim(line);
    if(line.back() == ';') line.pop_back();
    const auto pos = line.find(m_class_name + "::");
    //TODO finish
    return line;
}