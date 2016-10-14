#include "headerparser.hpp"

#include "commonparsing.hpp"

#include <iostream>

HeaderParser::HeaderParser(const boost::filesystem::path& file)
    : m_lines(Utils::loadFileAsStringList(file))
{
}

HeaderParser::HeaderParser(Utils::StringList_t lines)
    : m_lines(std::move(lines))
{
}

std::pair<std::string, Utils::StringList_t> HeaderParser::run()
{
    const auto class_name = CommonParsing::findClassName(m_lines);
    CommonParsing::removeUselessLines(m_lines);
    std::transform(begin(m_lines), end(m_lines), begin(m_lines), &Utils::trim);
    m_lines = CommonParsing::fuseSplittedLines(m_lines);
    std::transform(begin(m_lines), end(m_lines), begin(m_lines), &HeaderParser::cleanUpMethodSignature);
    return std::make_pair(class_name, m_lines);
}

std::string HeaderParser::cleanUpMethodSignature(std::string line)
{
    line = Utils::trim(line);
    if(Utils::startsWith(line, "explicit ")) line = line.substr(9);
    if(Utils::startsWith(line, "virtual ")) line = line.substr(8);
    if(line.back() == ';') line.pop_back();
    if(Utils::endsWith(line, " override")) line = line.substr(0, line.length() - 9);
    return line;
}