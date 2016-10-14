#include "utils.hpp"

#include <fstream>

#include <boost/filesystem.hpp>

#include <GSL/gsl_assert.h>

auto Utils::loadFileAsStringList(const boost::filesystem::path& file) -> StringList_t
{
    Expects(boost::filesystem::exists(file));
    std::ifstream input(file.string());
    StringList_t res;
    std::string line;
    while(std::getline(input, line))
    {
        line = trim(line);
        if(!line.empty()) res.push_back(line);
    }
    return res;
}

std::string Utils::trimLeft(std::string str)
{
    while(!str.empty() && std::isspace(str.front()))
        str.erase(begin(str));
    return str;
}

std::string Utils::trimRight(std::string str)
{
    while(!str.empty() && std::isspace(str.back()))
        str.pop_back();
    return str;
}

std::string Utils::trim(std::string str)
{
    return trimRight(trimLeft(str));
}

bool Utils::contains(const std::string& str, const std::string& token)
{
    return str.find(token) != std::string::npos;
}

bool Utils::startsWith(const std::string& str, const std::string& token)
{
    return str.size() >= token.size() && str.find(token) == 0;
}

bool Utils::endsWith(const std::string& str, const std::string& token)
{
    return str.size() >= token.size() && str.find(token) == str.size() - token.size();
}
