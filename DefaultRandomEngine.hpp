#pragma once

#include <random>

inline auto& defaultRandomEngine()
{
    using namespace std;
    thread_local mt19937 dre{random_device{}()}; // not using default_random_engine per Lavavej advice
    return dre;
}
