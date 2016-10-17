#include "commonparsing.hpp"

void CommonParsing::removeUselessLines(Utils::StringList_t& lines)
{
    auto it = std::remove_if(begin(lines), end(lines), [](const std::string& line) {
        return !Utils::contains(line, "(") && !Utils::contains(line, ")");
    });
    lines.erase(it, end(lines));
}

std::string CommonParsing::findClassName(const Utils::StringList_t& lines)
{
    Utils::StringList_t candidates;
    std::copy_if(begin(lines), end(lines), std::back_inserter(candidates), [](const std::string& line) {
        return Utils::contains(line, "class ") || Utils::contains(line, "struct ");
    });
    if(candidates.size() == 1) return cleanUpClassName(candidates.front());
    //    std::cout << "several candidates left :";
    //    std::copy(begin(candidates), end(candidates), std::ostream_iterator<std::string>(std::cout, ", "));
    //    std::cout << std::endl;
    auto it = std::remove_if(begin(candidates), end(candidates),
                             [](const std::string& line) { return Utils::contains(line, ";"); });
    candidates.erase(it, end(candidates));
    if(candidates.size() == 1) return cleanUpClassName(candidates.front());
    //    std::cout << "several candidates left :";
    //    std::copy(begin(candidates), end(candidates), std::ostream_iterator<std::string>(std::cout, ", "));
    //    std::cout << std::endl;
    throw std::runtime_error("Unable to find class name");
    return {};
}

Utils::StringList_t CommonParsing::fuseSplittedLines(const Utils::StringList_t& lines)
{
    Utils::StringList_t res;
    for(std::size_t i = 0; i < lines.size(); i++)
    {
        std::string tmp;
        auto j = i;
        std::size_t times_added = 0;
        for(; j < lines.size() && !Utils::endsWith(tmp, "; ") && tmp != "{ " && tmp != "} "
              && (lines[j] != "{" || tmp.empty());
            j++)
        {
            tmp += lines[j] + " ";
            times_added++;
        }
        if(tmp.size() > 1) tmp.pop_back();
        res.push_back(tmp);
        if(times_added > 1) i = j - 1;
    }
    return res;
}

std::string CommonParsing::cleanUpClassName(std::string line)
{
    line = Utils::trim(line);
    if(Utils::startsWith(line, "class ")) line = line.substr(6);
    if(Utils::startsWith(line, "struct ")) line = line.substr(7);
    const auto pos = line.find(':');
    if(pos != std::string::npos)
    {
        line = Utils::trim(line.substr(0, pos));
    }
    return line;
}
