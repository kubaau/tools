#pragma once

#include <iostream>

#define DEFINE_STRONG_TYPE(Name, UnderlyingType) using Name = Strong<UnderlyingType, struct StrongTag##Name>;

template <typename UnderlyingType, typename Tag>
class Strong
{
public:
    using Underlying = UnderlyingType;

    constexpr Strong(UnderlyingType v = {}) : value(v) {}

    auto operator=(UnderlyingType v)
    {
        value = v;
        return *this;
    }

    auto operator*() const { return value; }
    auto operator-> () const { return &value; }
    bool operator==(const Strong& other) const { return value == other.value; }
    bool operator!=(const Strong& other) const { return value != other.value; }
    bool operator<(const Strong& other) const { return value < other.value; }
    bool operator>(const Strong& other) const { return value > other.value; }
    auto operator<<(unsigned shift) const { return value << shift; }
    auto operator>>(unsigned shift) const { return value >> shift; }

    auto operator+=(unsigned operand) { return value += operand; }
    auto operator-=(unsigned operand) { return value -= operand; }
    auto operator++() { return ++value; }
    auto operator--() { return --value; }
    auto operator++(int) { return value++; }
    auto operator--(int) { return value--; }

private:
    UnderlyingType value;
};

template <typename UnderlyingType, typename Tag>
auto& operator<<(std::ostream& os, const Strong<UnderlyingType, Tag>& v)
{
    return os << *v;
}

namespace std
{
    template <typename T, typename Tag>
    struct hash<Strong<T, Tag>>
    {
        auto operator()(Strong<T, Tag> value) const { return hash<T>{}(*value); }
    };
}
