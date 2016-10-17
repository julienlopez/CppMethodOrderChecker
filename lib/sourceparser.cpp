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
    auto it = std::remove_if(begin(m_lines), end(m_lines),
                             [this](const std::string& line) { return Utils::startsWith(line, "#"); });
    m_lines.erase(it, end(m_lines));
    m_lines = CommonParsing::fuseSplittedLines(m_lines);
    CommonParsing::removeUselessLines(m_lines);
    it = std::remove_if(begin(m_lines), end(m_lines),
                        [this](const std::string& line) { return !Utils::contains(line, m_class_name + "::"); });
    m_lines.erase(it, end(m_lines));
    for(auto& line : m_lines)
        line = cleanUpMethodSignature(std::move(line));
    return m_lines;
}

std::string SourceParser::cleanUpMethodSignature(std::string line) const
{
    line = Utils::trim(line);
    if(line.back() == ';') line.pop_back();
    line = removeClassPrefix(std::move(line));
    line = removeInitializationList(std::move(line));
    line = removeDefault(std::move(line));
    return Utils::trim(line);
}

std::string SourceParser::removeClassPrefix(std::string line) const
{
    const auto prefix = m_class_name + "::";
    const auto pos = line.find(prefix);
    assert(pos != std::string::npos);
    line.erase(begin(line) + pos, begin(line) + pos + prefix.size());
    return line;
}

std::string SourceParser::removeInitializationList(std::string line)
{
    const auto pos = line.find(":");
    if(pos != std::string::npos && line[pos + 1] != ':') line = line.substr(0, pos);
    return line;
}

std::string SourceParser::removeDefault(std::string line)
{
    if(Utils::endsWith(line, " default"))
    {
        const auto pos = line.find("=");
        assert(pos != std::string::npos);
        line = line.substr(0, pos);
    }
    return Utils::trim(line);
}