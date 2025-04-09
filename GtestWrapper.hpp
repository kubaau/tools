#undef COLOR_RED
#undef COLOR_GREEN
#undef COLOR_YELLOW
#include <gtest/gtest.h>

#include <thread>

#include "Print.hpp"
#include "Typedefs.hpp"

#define EXPECT_CONTAINS(c, v) EXPECT_TRUE(c.contains(v))
#define EXPECT_NOT_CONTAINS(c, v) EXPECT_FALSE(c.contains(v))
#define EXPECT_EMPTY(c) EXPECT_TRUE(c.empty())
#define EXPECT_SIZE(c, sz) EXPECT_EQ(c.size(), sz)

using namespace std;
using namespace testing;

using V = vector<int>;
using Vu = vector<unsigned>;
using Vu = vector<unsigned>;
using Vf = vector<float>;
using Vd = vector<double>;
using Vs = vector<string>;
using V8 = vector<u8>;
using Vsz = vector<size_t>;
using S = set<int>;
using US = unordered_set<int>;
using M = map<int, int>;
using UM = unordered_map<int, int>;

template <unsigned n, typename T = int>
using A = array<T, n>;
