#include "analyzer.hpp"
#include "headerparser.hpp"
#include "sourceparser.hpp"

#include <boost/filesystem.hpp>

#include <iostream>

Analyzer::Analyzer(const boost::filesystem::path& file)
    : m_header_file(file.parent_path() / (file.stem().string() + ".hpp"))
    , m_source_file(file.parent_path() / (file.stem().string() + ".cpp"))
{
    if(!boost::filesystem::exists(m_header_file) || !boost::filesystem::exists(m_source_file))
        throw std::runtime_error("can't find both source file and header file");
    std::tie(m_class_name, m_header_methods) = HeaderParser(m_header_file).run();

    std::cout << "Class found: " << m_class_name << std::endl;
    std::cout << m_header_methods.size() << std::endl;
    std::copy(begin(m_header_methods), end(m_header_methods), std::ostream_iterator<std::string>(std::cout, "\n"));
    std::cout << std::endl;

    m_source_methods = SourceParser(m_class_name, m_source_file).run();

    std::cout << m_source_methods.size() << std::endl;
    std::copy(begin(m_source_methods), end(m_source_methods), std::ostream_iterator<std::string>(std::cout, "\n"));
    std::cout << std::endl;

    parseCompareBothMethods();
}

void Analyzer::parseCompareBothMethods()
{
}