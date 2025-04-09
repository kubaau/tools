#include "History.hpp"

#include "GtestWrapper.hpp"

using namespace HistoryTypes;
using namespace this_thread;

TEST(History, history_basic)
{
    History<int> h;
    h.insert(1);
    EXPECT_CONTAINS(h, 1);
    EXPECT_NOT_CONTAINS(h, 2);
    h.insert(2);
    EXPECT_CONTAINS(h, 1);
    EXPECT_CONTAINS(h, 2);
    EXPECT_SIZE(h, 2);

    h.set_expiration_period(1ms);
    sleep_for(1ms);
    h.purge();
    EXPECT_EMPTY(h);
}

TEST(History, history_basic_string)
{
    History<string> h;
    h.insert("abc");
    EXPECT_CONTAINS(h, "abc");
    EXPECT_NOT_CONTAINS(h, "def");
    h.insert("def");
    EXPECT_CONTAINS(h, "abc");
    EXPECT_CONTAINS(h, "def");
    EXPECT_SIZE(h, 2);

    h.set_expiration_period(1ms);
    sleep_for(1ms);
    h.purge();
    EXPECT_EMPTY(h);
}

TEST(History, history_with_expiration)
{
    History<int> h{ExpirationPeriod{1ms}};
    h.insert(1);
    EXPECT_CONTAINS(h, 1);
    h.insert(2);
    EXPECT_CONTAINS(h, 1);
    EXPECT_CONTAINS(h, 2);
    EXPECT_SIZE(h, 2);

    sleep_for(1ms);
    EXPECT_NOT_CONTAINS(h, 1);
    EXPECT_NOT_CONTAINS(h, 2);
    EXPECT_EMPTY(h);
}

TEST(History, history_always_purge)
{
    History<int> h{ExpirationPeriod{1ms}, PurgePeriod{PurgePeriod::zero()}};
    h.insert(1);
    EXPECT_CONTAINS(h, 1);
    sleep_for(1ms);
    h.insert(2);
    EXPECT_NOT_CONTAINS(h, 1);
    EXPECT_CONTAINS(h, 2);
    EXPECT_SIZE(h, 1);

    h.set_expiration_period(100us);
    sleep_for(100us);
    h.purge();
    EXPECT_EMPTY(h);
}

TEST(History, DISABLED_history_complex_scenario)
{
    History<int> h{ExpirationPeriod{1s}, PurgePeriod{2s}};

    h.insert(1); // 0
    EXPECT_SIZE(h, 1);

    h.insert(2); // 0
    EXPECT_SIZE(h, 2);

    sleep_for(100ms);
    h.insert(3); // 100
    EXPECT_SIZE(h, 3);

    sleep_for(200ms);
    h.insert(4); // 300
    EXPECT_SIZE(h, 4);

    sleep_for(200ms);
    h.insert(5); // 500
    h.insert(6); // 500
    EXPECT_SIZE(h, 6);

    sleep_for(200ms);
    h.insert(7); // 700
    EXPECT_SIZE(h, 7);

    sleep_for(300ms);
    h.insert(8); // 1000
    EXPECT_SIZE(h, 8);
    EXPECT_NOT_CONTAINS(h, 1);
    EXPECT_NOT_CONTAINS(h, 2);
    EXPECT_SIZE(h, 6);

    sleep_for(500ms);
    h.insert(9); // 1500
    EXPECT_SIZE(h, 7);

    sleep_for(500ms);
    h.insert(10); // 2000
    EXPECT_SIZE(h, 2);

    sleep_for(2s);
    h.insert(11);
    EXPECT_SIZE(h, 1);

    sleep_for(1s);
    EXPECT_NOT_CONTAINS(h, 11);
    EXPECT_EMPTY(h);
}
