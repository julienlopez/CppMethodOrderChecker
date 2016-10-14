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
    CommonParsing::removeUselessLines(m_lines);
    std::transform(begin(m_lines), end(m_lines), begin(m_lines), &Utils::trim);
    m_lines = CommonParsing::fuseSplittedLines(m_lines);
    auto it = std::remove_if(begin(m_lines), end(m_lines),
                             [this](const std::string& line) { return !Utils::contains(line, m_class_name + "::"); });
    m_lines.erase(it, end(m_lines));
    // std::cout << m_lines.size() << std::endl;
    // std::copy(begin(m_lines), end(m_lines), std::ostream_iterator<std::string>(std::cout, "\n"));
    // std::cout << std::endl;
    return {};
}