#include "analyzer.hpp"
#include "headerparser.hpp"
#include "sourceparser.hpp"

#include <boost/filesystem.hpp>
#include <boost/iterator/zip_iterator.hpp>

#include <iostream>

Analyzer::Analyzer(const boost::filesystem::path& file)
    : m_header_file(file.parent_path() / (file.stem().string() + ".hpp"))
    , m_source_file(file.parent_path() / (file.stem().string() + ".cpp"))
{
    if(!boost::filesystem::exists(m_header_file) || !boost::filesystem::exists(m_source_file))
        throw std::runtime_error("can't find both source file and header file");
    std::tie(m_class_name, m_header_methods) = HeaderParser(m_header_file).run();

    // std::cout << "Class found: " << m_class_name << std::endl;
    // std::cout << m_header_methods.size() << std::endl;
    // std::copy(begin(m_header_methods), end(m_header_methods), std::ostream_iterator<std::string>(std::cout, "\n"));
    // std::cout << std::endl;

    m_source_methods = SourceParser(m_class_name, m_source_file).run();

    // std::cout << m_source_methods.size() << std::endl;
    // std::copy(begin(m_source_methods), end(m_source_methods), std::ostream_iterator<std::string>(std::cout, "\n"));
    // std::cout << std::endl;

    parseCompareBothMethods();
}

bool Analyzer::parseCompareBothMethods() const
{
    if(m_source_methods.size() != m_header_methods.size())
    {
        std::cout << "Not the same number of methods found." << std::endl;
        return true;
    }
    bool error_found = false;
    for(auto it = boost::make_zip_iterator(boost::make_tuple(begin(m_header_methods), begin(m_source_methods)));
        it != boost::make_zip_iterator(boost::make_tuple(end(m_header_methods), end(m_source_methods))); ++it)
    {
        //std::cout << it->get<0>() << " =?= " << it->get<1>() << std::endl;
        if(cleanMethodSignature(it->get<0>()) != cleanMethodSignature(it->get<1>()))
        {
            error_found = true;
            std::cout << "differences found:\n\t" << it->get<0>() << "\n\t" << it->get<1>() << std::endl;
        }
    }
    if(!error_found)
        std::cout << "nothing to whine about" << std::endl;
    return !error_found;
}

std::string Analyzer::cleanMethodSignature(std::string line)
{
    if(Utils::startsWith(line, "auto ") && Utils::contains(line, "->"))
    {
        const auto pos = line.find("->");
        assert(pos != std::string::npos);
        const auto method = Utils::trim(line.substr(4, pos - 4));
        const auto type = Utils::trim(line.substr(pos + 2));
        return type + " " + method;
    }
    return line;
}