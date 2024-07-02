#pragma once

#include "PtrMagic.hpp"

template <class Struct, typename Member>
auto offsetOfMember(Member Struct::*member)
{
    const Struct s{};
    return asBytePtr(&(s.*member)) - asBytePtr(&s);
}
