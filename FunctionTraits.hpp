#pragma once

#include <functional>
#include <type_traits>

template <class Signature>
struct FunctionTraits : public FunctionTraits<decltype(&Signature::operator())>
{
};

template <typename Result, typename... Args>
struct FunctionTraits<Result (*)(Args...)>
{
    using ResultType = Result;
    using Function = std::function<Result(Args...)>;

    template <size_t N>
    using ArgType = std::tuple_element_t<N, std::tuple<Args...>>;
};

template <typename Result, typename Class, typename... Args>
struct FunctionTraits<Result (Class::*)(Args...) const> : public FunctionTraits<Result (*)(Args...)>
{
};

template <typename Result, typename Class, typename... Args>
struct FunctionTraits<Result (Class::*)(Args...)> : public FunctionTraits<Result (*)(Args...)>
{
};

template <typename T>
std::false_type isFunction(T, float);

template <class T>
std::true_type isFunction(T, int, typename FunctionTraits<T>::Function* = nullptr);

template <typename T>
using IsFunction = decltype(isFunction(std::declval<T>(), 0));
