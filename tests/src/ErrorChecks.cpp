#include "ErrorChecks.hpp"
#include "GtestWrapper.hpp"

TEST(ErrorChecks, appendErrno)
{
    ostringstream oss;
    errno = 10;
    appendErrno(oss);
    const auto s = oss.str();
    EXPECT_FALSE(s.empty());
    print(s);
}

TEST(ErrorChecks, die)
{
    EXPECT_THROW(die(__FUNCTION__, 17), runtime_error);
}

TEST(ErrorChecks, log_exceptions)
{
    try
    {
        throw runtime_error{""};
    }
    LOG_EXCEPTIONS
    try
    {
        throw int{};
    }
    LOG_EXCEPTIONS
}

namespace
{
    bool succeededFoo(int i) { return not i; }
    bool failedBar(void* p) { return not p; }

    GENERATE_CHECK(Foo)
    GENERATE_REVERSE_CHECK(Bar)
}

TEST(ErrorChecks, generate_check)
{
    EXPECT_NO_THROW(checkFoo(0));
    EXPECT_THROW(checkFoo(1), runtime_error);
}

TEST(ErrorChecks, generate_reverse_check)
{
    int i;
    EXPECT_NO_THROW(checkBar(&i));
    int* p = nullptr;
    EXPECT_THROW(checkBar(p), runtime_error);
}
