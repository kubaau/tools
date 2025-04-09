#include "HistorySimple.hpp"

#include "GtestWrapper.hpp"

using namespace this_thread;

TEST(HistorySimple, history_simple_basic_string)
{
    HistorySimple h;
    h.insert("abc");
    EXPECT_CONTAINS(h, "abc");
    EXPECT_NOT_CONTAINS(h, "def");
    h.insert("def");
    EXPECT_CONTAINS(h, "abc");
    EXPECT_CONTAINS(h, "def");
    EXPECT_SIZE(h, 2);

    h.set_expiration_period(1ms);
    sleep_for(1ms);
    EXPECT_NOT_CONTAINS(h, "abc");
    EXPECT_NOT_CONTAINS(h, "def");
}

TEST(HistorySimple, history_simple_with_expiration)
{
    HistorySimple h{1ms};
    h.insert("abc");
    EXPECT_CONTAINS(h, "abc");
    h.insert("def");
    EXPECT_CONTAINS(h, "abc");
    EXPECT_CONTAINS(h, "def");
    EXPECT_SIZE(h, 2);

    sleep_for(1ms);
    EXPECT_NOT_CONTAINS(h, "abc");
    EXPECT_NOT_CONTAINS(h, "def");
    EXPECT_EMPTY(h);
}

TEST(HistorySimple, DISABLED_history_simple_complex_scenario)
{
    HistorySimple h{1s};

    h.insert("aaa"); // 0
    EXPECT_SIZE(h, 1);

    h.insert("bbb"); // 0
    EXPECT_SIZE(h, 2);

    sleep_for(100ms);
    h.insert("ccc"); // 100
    EXPECT_SIZE(h, 3);

    sleep_for(200ms);
    h.insert("ddd"); // 300
    EXPECT_SIZE(h, 4);

    sleep_for(200ms);
    h.insert("eee"); // 500
    h.insert("fff"); // 500
    EXPECT_SIZE(h, 6);

    sleep_for(200ms);
    h.insert("ggg"); // 700
    EXPECT_SIZE(h, 7);

    sleep_for(300ms);
    h.insert("hhh"); // 1000
    EXPECT_SIZE(h, 8);
    EXPECT_NOT_CONTAINS(h, "aaa");
    EXPECT_NOT_CONTAINS(h, "bbb");
    EXPECT_SIZE(h, 6);

    sleep_for(500ms);
    h.insert("iii"); // 1500
    EXPECT_SIZE(h, 7);
    EXPECT_NOT_CONTAINS(h, "ccc");
    EXPECT_NOT_CONTAINS(h, "ddd");
    EXPECT_NOT_CONTAINS(h, "eee");
    EXPECT_NOT_CONTAINS(h, "fff");
    EXPECT_CONTAINS(h, "ggg");
    EXPECT_SIZE(h, 3);

    sleep_for(500ms);
    h.insert("jjj"); // 2000
    EXPECT_SIZE(h, 4);
    EXPECT_NOT_CONTAINS(h, "ggg");
    EXPECT_NOT_CONTAINS(h, "hhh");
    EXPECT_SIZE(h, 2);

    sleep_for(2s);
    h.insert("kkk");
    EXPECT_SIZE(h, 3);
    EXPECT_NOT_CONTAINS(h, "iii");
    EXPECT_NOT_CONTAINS(h, "jjj");
    EXPECT_SIZE(h, 1);

    sleep_for(1s);
    EXPECT_NOT_CONTAINS(h, "kkk");
    EXPECT_EMPTY(h);
}
