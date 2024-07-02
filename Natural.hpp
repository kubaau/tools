#pragma once

#include <stdexcept>
#include "TypeTraits.hpp"
#include "Typedefs.hpp"

class Natural
{
    int n;

public:
    constexpr Natural(int n = 0) : n(n)
    {
        if (n < 0)
            throw std::range_error{"Negative natural value"};
    }

    constexpr operator int() const { return n; }

    // macro/operator crap follows, not worth reading from here on

    constexpr Natural& operator++() { return *this += 1; }
    constexpr Natural& operator--() { return *this -= 1; }
    constexpr Natural operator++(int)
    {
        const auto ret = *this;
        ++*this;
        return ret;
    }
    constexpr Natural operator--(int)
    {
        const auto ret = *this;
        --*this;
        return ret;
    }

#define DEFINE_COMPARISON_OPERATOR_INSIDE(Op)                  \
    template <typename T>                                      \
    constexpr bool operator Op(T other) const                  \
    {                                                          \
        return static_cast<i64>(n) Op static_cast<i64>(other); \
    }

#define DEFINE_COMPARISON_OPERATOR_OUTSIDE(Op, OppositeOp)                     \
    template <typename T, typename = DisableIfType<IsSameDecayed<T, Natural>>> \
    constexpr bool operator Op(T lhs, Natural rhs)                             \
    {                                                                          \
        return rhs OppositeOp lhs;                                             \
    }

#define DEFINE_ASSIGNMENT_OPERATOR(Op)      \
    template <typename T>                   \
    constexpr Natural& operator Op(T other) \
    {                                       \
        auto v = n;                         \
        v Op other;                         \
        return *this = v;                   \
    }

    DEFINE_COMPARISON_OPERATOR_INSIDE(==)
    DEFINE_COMPARISON_OPERATOR_INSIDE(!=)
    DEFINE_COMPARISON_OPERATOR_INSIDE(<)
    DEFINE_COMPARISON_OPERATOR_INSIDE(>)
    DEFINE_COMPARISON_OPERATOR_INSIDE(<=)
    DEFINE_COMPARISON_OPERATOR_INSIDE(>=)

    DEFINE_ASSIGNMENT_OPERATOR(+=)
    DEFINE_ASSIGNMENT_OPERATOR(-=)
    DEFINE_ASSIGNMENT_OPERATOR(*=)
    DEFINE_ASSIGNMENT_OPERATOR(/=)
    DEFINE_ASSIGNMENT_OPERATOR(%=)
    DEFINE_ASSIGNMENT_OPERATOR(&=)
    DEFINE_ASSIGNMENT_OPERATOR(|=)
    DEFINE_ASSIGNMENT_OPERATOR(<<=)
    DEFINE_ASSIGNMENT_OPERATOR(>>=)
};

//DEFINE_COMPARISON_OPERATOR_OUTSIDE(==, ==)
DEFINE_COMPARISON_OPERATOR_OUTSIDE(!=, !=)
DEFINE_COMPARISON_OPERATOR_OUTSIDE(<, >)
DEFINE_COMPARISON_OPERATOR_OUTSIDE(>, <)
DEFINE_COMPARISON_OPERATOR_OUTSIDE(<=, >=)
DEFINE_COMPARISON_OPERATOR_OUTSIDE(>=, <=)

#undef DEFINE_COMPARISON_OPERATOR_INSIDE
#undef DEFINE_COMPARISON_OPERATOR_OUTSIDE
#undef DEFINE_ASSIGNMENT_OPERATOR
