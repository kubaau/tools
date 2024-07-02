#pragma once

#include <sstream>

#include "FileCommon.hpp"

inline auto readBinaryFile(FilePath path)
{
    using namespace std;

    auto file = openFile(path, ios::in | ios::binary);

    jumpToEnd(file);
    IOBuffer data(static_cast<size_t>(file.tellg()));

    jumpToStart(file);
    file.read(data.data(), data.size());
    return data;
}

inline auto readTextFile(FilePath path)
{
    std::ostringstream oss;
    oss << openFile(path).rdbuf();
    return oss.str();
}
