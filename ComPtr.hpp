#pragma once

#include <wrl/client.h>

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

template <class T>
auto& operator*(const ComPtr<T>& com_ptr)
{
    return *com_ptr.Get();
}
