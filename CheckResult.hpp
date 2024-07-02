#pragma once

#include <stdexcept>
#include <string>

template <class Result>
void check(const Result& result, std::string msg = "")
{
    if (not result)
        throw std::runtime_error{msg};
}
