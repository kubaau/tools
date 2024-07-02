#ifdef _WIN32
#include "WeakPtrMatcher.hpp"
#include "GtestWrapper.hpp"

struct SMock
{
    MOCK_METHOD1(foo, void(weak_ptr<int>));
};

TEST(WeakPtrMatcher, weak_ptr_matcher)
{
    SMock smok;
    auto sp = make_shared<int>();
    EXPECT_CALL(smok, foo(WeakPtrMatcher(sp.get())));
    smok.foo(sp);
}
#endif
