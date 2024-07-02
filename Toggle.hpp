#pragma once

inline auto toggle(bool& flag) noexcept
{
    return flag = not flag;
}
