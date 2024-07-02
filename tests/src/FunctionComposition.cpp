#include "FunctionComposition.hpp"
#include "GtestWrapper.hpp"

TEST(FunctionComposition, compose)
{
    auto f1 = [](int n) { return n += 2; };
    auto f2 = [](int n) { return n *= 3; };
    auto c = compose(f1, f2);
    EXPECT_EQ(6, c(0));
    EXPECT_EQ(9, c(1));
}

TEST(FunctionComposition, FunctorComposite)
{
    int i = 0;
    auto f1 = [&i](int n) { i += n; };
    auto f2 = [&i](int n) { return i *= n; };
    auto c = FunctorComposite<void(int)>{f1, f2};
    c(3);
    EXPECT_EQ(9, i);
    i = 0;
    c(4);
    EXPECT_EQ(16, i);
}
