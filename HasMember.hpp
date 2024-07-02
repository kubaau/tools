#pragma once

#include "TypeTraits.hpp"

namespace Sfinae
{
    using yes = char;
    using no = struct
    {
        char c[2];
    };
} // namespace Sfinae

#define GENERATE_HAS_MEMBER(member)                                                          \
    template <class T, typename = EnableIf<std::is_class_v<T>>>                              \
    class HasMember_##member                                                                 \
    {                                                                                        \
    private:                                                                                 \
        struct Fallback                                                                      \
        {                                                                                    \
            int member;                                                                      \
        };                                                                                   \
        struct Derived : T, Fallback                                                         \
        {                                                                                    \
        };                                                                                   \
        template <typename U>                                                                \
        static Sfinae::no& test(decltype(U::member)*);                                       \
        template <class U>                                                                   \
        static Sfinae::yes& test(...);                                                       \
                                                                                             \
    public:                                                                                  \
        static constexpr auto value = sizeof(test<Derived>(nullptr)) == sizeof(Sfinae::yes); \
    };
