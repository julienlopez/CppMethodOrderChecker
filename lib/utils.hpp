#pragma once

#include <string>
#include <vector>

#include <boost/filesystem/path.hpp>

namespace Utils
{

    using StringList_t = std::vector<std::string>;

    /**
     * @pre file exists
     */
    StringList_t loadFileAsStringList(const boost::filesystem::path& file);

    std::string trimLeft(std::string str);

    std::string trimRight(std::string str);

    std::string trim(std::string str);

    bool contains(const std::string& str, const std::string& token);

    bool startsWith(const std::string& str, const std::string& token);

    bool endsWith(const std::string& str, const std::string& token);
}
