#pragma once

#include "FileCommon.hpp"

template <class C>
auto writeFile(FilePath path, const C& data, std::ios::openmode additional_open_mode = {})
{
    using namespace std;
    openFile(path, ios::out | ios::trunc | additional_open_mode).write(data.data(), data.size());
}

inline auto writeBinaryFile(FilePath path, const IOBuffer& data)
{
    writeFile(path, data, std::ios::binary);
}

inline auto writeTextFile(FilePath path, const std::string& data)
{
    writeFile(path, data);
}
