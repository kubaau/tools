#pragma once

#include <cstdlib>

#include "As.hpp"

template <typename T>
auto mallocT(size_t count)
{
    using namespace std;
    return asPtr<T>(malloc(count * sizeof(T)));
}

template <typename T>
auto callocT(size_t count)
{
    using namespace std;
    return asPtr<T>(calloc(count, sizeof(T)));
}

template <typename T>
auto reallocT(void* ptr, size_t count)
{
    using namespace std;
    return asPtr<T>(realloc(ptr, count * sizeof(T)));
}

template <typename T = void*>
auto aligned_allocT(size_t alignment, size_t size)
{
    using namespace std;
#ifndef _WIN32
    return asPtr<T>(aligned_alloc(alignment, size));
#else
    return asPtr<T>(_aligned_malloc(size, alignment));
#endif
}
