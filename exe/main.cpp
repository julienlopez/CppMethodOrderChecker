#include "analyzer.hpp"

#include <iostream>

#include <boost/filesystem.hpp>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr << "expected file name (either .cpp or .hpp)" << std::endl;
        return 1;
    }
    boost::filesystem::path file(argv[1]);
    if(!boost::filesystem::exists(file))
    {
        std::cerr << file << "doesn't exist" << std::endl;
        return 1;
    }
    std::cout << "analyzing " << file << std::endl;
    try
    {
        Analyzer a(file);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception : " << e.what() << std::endl;
        return 2;
    }
    return 0;
}
