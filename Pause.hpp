#pragma once

#include <iostream>

inline void pauseIO()
{
    std::cin.get();
}

inline void winIoPause()
{
#ifdef _WIN32
    system("pause");
#endif
}
