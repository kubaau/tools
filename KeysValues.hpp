#pragma once

#include <vector>

template <class Map>
auto keys(const Map& map)
{
    std::vector<typename Map::key_type> ret;
    ret.reserve(map.size());
    for (const auto& item : map)
        ret.push_back(item.first);
    return ret;
}

template <class Map>
auto values(const Map& map)
{
    std::vector<typename Map::mapped_type> ret;
    ret.reserve(map.size());
    for (const auto& item : map)
        ret.push_back(item.second);
    return ret;
}
