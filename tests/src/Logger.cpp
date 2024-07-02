#include "Logger.hpp"
#include "GtestWrapper.hpp"

TEST(Logger, logger_op)
{
    Logger logger;

    V v = {1, 2, 3};
    logger << v;

    S s = {3, 2, 1};
    logger << s;

    M m{{1, 2}, {3, 4}, {5, 6}};
    logger << m;

    logger << v << " / " << s << " / " << m << " - wow!";
}
