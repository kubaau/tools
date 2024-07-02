#pragma once

#ifdef _WIN32
#include <Windows.h>

inline void enableWinDebug()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
#else
inline void enableWinDebug() {}
#endif
