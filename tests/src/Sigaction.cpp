#ifndef _WIN32
#include "Sigaction.hpp"
#include "GtestWrapper.hpp"

static int counter;

static SigActionSignature(foo)
{
    ++counter;
}

TEST(Sigaction, installSigaction)
{
    counter = 0;
    installSigaction(SIGCONT, foo);
    raise(SIGCONT);
    EXPECT_EQ(1, counter);
}

TEST(Sigaction, installSigaction_multiple)
{
    counter = 0;
    installSigaction({SIGCONT, SIGALRM}, foo);
    raise(SIGCONT);
    raise(SIGALRM);
    EXPECT_EQ(2, counter);
}

TEST(Sigaction, failedSigaction)
{
    EXPECT_TRUE(failedSigaction(-1));
    EXPECT_FALSE(failedSigaction(0));
    EXPECT_TRUE(failedSigaction(1));
}
#endif
