#pragma once

#include <fstream>

#include "CheckResult.hpp"
#include "IoTypedefs.hpp"
#include "Typedefs.hpp"

inline void jump(std::fstream& file, std::ios_base::seekdir pos)
{
    file.seekg(0, pos);
}

inline void jumpToStart(std::fstream& file)
{
    jump(file, std::ios_base::beg);
}

inline void jumpToEnd(std::fstream& file)
{
    jump(file, std::ios_base::end);
}

inline auto openFile(FilePath path, std::ios::openmode mode = std::ios::in)
{
    std::fstream file{path, mode};
    check(file, "Cannot open " + path.string());
    return file;
}
