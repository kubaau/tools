#include "Std.hpp"
#include <gtest/gtest.h>

TEST(Std, namespaces)
{
    seconds s{7};
    cout << s.count() << endl;
}
