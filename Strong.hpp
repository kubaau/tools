#pragma once

#include <ostream>

#define DEFINE_STRONG_TYPE(Name, UnderlyingType) using Name = Strong<UnderlyingType, struct StrongTag##Name>;

template <typename UnderlyingType, typename Tag>
class Strong
{
public:
    using Underlying = UnderlyingType;

    constexpr Strong(UnderlyingType v = {}) : value{v} {}

    constexpr auto& operator=(UnderlyingType v)
    {
        value = v;
        return *this;
    }

    constexpr auto& operator*() const { return value; }
    constexpr auto operator->() const { return &value; }

    constexpr auto operator<=>(const Strong&) const = default;

    constexpr auto operator<<(unsigned shift) const { return value << shift; }
    constexpr auto operator>>(unsigned shift) const { return value >> shift; }

    constexpr auto operator+=(unsigned operand) { return value += operand; }
    constexpr auto operator-=(unsigned operand) { return value -= operand; }
    constexpr auto operator++() { return ++value; }
    constexpr auto operator--() { return --value; }
    constexpr auto operator++(int) { return value++; }
    constexpr auto operator--(int) { return value--; }

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
