#pragma once

#include <gmock/gmock.h>

MATCHER_P(WeakPtrMatcher, to, "")
{
    (void)result_listener;
    return arg.lock().get() == to;
}
