#include "Loud.hpp"
#include "GtestWrapper.hpp"

TEST(Loud, loud)
{
    Loud l1 = 1;
    Loud l2 = 2;
    Loud l3 = 3;
    Loud l1c = l1;
    l3 = l2;
    Loud l4 = move(l3);
    l4 = Loud{5};
    ++l1;
    l1++;
    EXPECT_EQ(3, static_cast<int>(l1));
}
