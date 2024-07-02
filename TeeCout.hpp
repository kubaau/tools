#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/tee.hpp>
#include <fstream>
#include <iostream>

class TeeCout
{
public:
    using TeeDevice = boost::iostreams::tee_device<std::ostream, std::ofstream>;
    using TeeStream = boost::iostreams::stream<TeeDevice>;

    TeeCout(std::string filename = "cout.txt")
        : file(filename, std::ofstream::trunc), cout_orig(std::cout.rdbuf()), device(cout_orig, file), stream(device)
    {
        std::cout.rdbuf(stream.rdbuf());
    }

    ~TeeCout()
    {
        stream.flush();
        stream.close();
        std::cout.rdbuf(cout_orig.rdbuf());
    }

private:
    std::ofstream file;
    std::ostream cout_orig;
    TeeDevice device;
    TeeStream stream;
};
