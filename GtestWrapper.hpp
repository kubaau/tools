#undef COLOR_RED
#undef COLOR_GREEN
#undef COLOR_YELLOW
#include <gtest/gtest.h>

#include <thread>

#include "Print.hpp"
#include "Typedefs.hpp"

using namespace std;
using namespace testing;

using V = vector<int>;
using Vu = vector<unsigned>;
using Vu = vector<unsigned>;
using Vf = vector<float>;
using Vd = vector<double>;
using Vs = vector<string>;
using V8 = vector<u8>;
using S = set<int>;
using M = map<int, int>;

template <unsigned n, typename T = int>
using A = array<T, n>;
