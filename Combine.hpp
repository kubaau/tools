#pragma once

#define COMBINE_IMPL(X, Y) X##Y
#define COMBINE(X, Y) COMBINE_IMPL(X, Y)
#define LINE_COMBINE(name) COMBINE(name, __LINE__)
