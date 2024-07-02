#pragma once

#include <boost/functional/hash.hpp>

template <typename T>
struct HashMembers
{
    auto operator()(const T& val) const { return boost::hash_value(val.tieAll()); }
};
