#pragma once

#include <algorithm>
#include <string>
#include <vector>

using Arg = std::string;
using Args = std::vector<Arg>;
inline auto readArgs(int argc, char* argv[])
{
    using namespace std;
    Args args(argc);
    copy_n(argv, argc, begin(args));
    return args;
}
