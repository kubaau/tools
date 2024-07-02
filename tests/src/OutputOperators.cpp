#include "OutputOperators.hpp"
#include "GtestWrapper.hpp"
#include "StringStream.hpp"

TEST(OutputOperators, op_it_pair_and_container)
{
    ostringstream oss1;
    ostringstream oss2;

    V v = {1, 2, 3};
    oss1 << make_pair(cbegin(v), cend(v));
    oss2 << v;
    EXPECT_EQ("{1, 2, 3}", oss1.str());
    EXPECT_EQ(oss1.str(), oss2.str());
    clear(oss1);
    clear(oss2);

    v.clear();
    oss1 << make_pair(cbegin(v), cend(v));
    oss2 << v;
    EXPECT_EQ("{}", oss1.str());
    EXPECT_EQ(oss1.str(), oss2.str());
    clear(oss1);
    clear(oss2);

    S s = {3, 2, 1};
    oss1 << make_pair(cbegin(s), cend(s));
    oss2 << s;
    EXPECT_EQ("{1, 2, 3}", oss1.str());
    EXPECT_EQ(oss1.str(), oss2.str());
    clear(oss1);
    clear(oss2);

    M m{{1, 2}, {3, 4}, {5, 6}};
    oss1 << make_pair(cbegin(m), cend(m));
    oss2 << m;
    EXPECT_EQ("{{1, 2}, {3, 4}, {5, 6}}", oss1.str());
    EXPECT_EQ(oss1.str(), oss2.str());
    clear(oss1);
    clear(oss2);
}

TEST(OutputOperators, op_pair)
{
    ostringstream oss;

    oss << make_pair(1, 2);
    EXPECT_EQ("{1, 2}", oss.str());
    clear(oss);

    oss << make_pair(string{"abc"}, string{"def"});
    EXPECT_EQ("{abc, def}", oss.str());
    clear(oss);
}

TEST(OutputOperators, op_stack)
{
    stack<int> s;
    ostringstream oss;

    oss << s;
    EXPECT_EQ("{}", oss.str());
    clear(oss);

    s.push(1);
    oss << s;
    EXPECT_EQ("{1}", oss.str());
    clear(oss);

    s.push(2);
    oss << s;
    EXPECT_EQ("{2, 1}", oss.str());
    clear(oss);

    s.push(3);
    oss << s;
    EXPECT_EQ("{3, 2, 1}", oss.str());
    clear(oss);
}

TEST(OutputOperators, op_queue)
{
    queue<int> q;
    ostringstream oss;

    oss << q;
    EXPECT_EQ("{}", oss.str());
    clear(oss);

    q.push(1);
    oss << q;
    EXPECT_EQ("{1}", oss.str());
    clear(oss);

    q.push(2);
    oss << q;
    EXPECT_EQ("{1, 2}", oss.str());
    clear(oss);

    q.push(3);
    oss << q;
    EXPECT_EQ("{1, 2, 3}", oss.str());
    clear(oss);
}

TEST(OutputOperators, op_tuple)
{
    ostringstream oss;

    oss << tuple<int, string, double>{3, "pi", 3.14};
    EXPECT_EQ("[3, pi, 3.14]", oss.str());
    clear(oss);

    oss << tuple<int>{4};
    EXPECT_EQ("[4]", oss.str());
    clear(oss);

    oss << tuple<>{};
    EXPECT_EQ("[]", oss.str());
    clear(oss);
}
