#pragma once

#include <iostream>

#include "WinDebug.hpp"

class ConsoleWindow
{
public:
    ConsoleWindow()
    {
        AllocConsole();
        MoveWindow(GetConsoleWindow(), 800, 0, 1000, 1000, true);
        DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
        freopen_s(&output, "CONOUT$", "w", stdout);
    }
    ~ConsoleWindow() { fclose(output); }

private:
    FILE* output;
};

inline void enableDebugConsole()
{
    enableWinDebug();
    static ConsoleWindow cw;
}
