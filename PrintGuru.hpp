#pragma once

#include "Args.hpp"

#ifndef _WIN32
#include <curses.h>
#include "Contains.hpp"
#include "RandomChance.hpp"
#include "Repeat.hpp"
#include "Sigaction.hpp"

#define NCURSES_ERROR_IF(Condition) \
    if (Condition)                  \
    return false

inline auto createTop(std::size_t width)
{
    std::ostringstream oss;
    oss << "\u250F";
    repeat(width - 2) oss << "\u2501";
    oss << "\u2513";
    return oss.str();
}

inline auto createBottom(std::size_t width)
{
    std::ostringstream oss;
    oss << "\u2517";
    repeat(width - 2) oss << "\u2501";
    oss << "\u251B";
    return oss.str();
}

inline auto heavy_border(WINDOW* window)
{
    constexpr auto side = "\u2503";

    int height, width;
    getmaxyx(window, height, width);

    NCURSES_ERROR_IF(mvwaddstr(window, 0, 0, createTop(width).c_str()) == ERR);
    repeat(height - 2)
    {
        NCURSES_ERROR_IF(mvwaddstr(window, i + 1, 0, side) == ERR);
        NCURSES_ERROR_IF(mvwaddstr(window, i + 1, width - 1, side) == ERR);
    }
    mvwaddstr(window, height - 1, 0, createBottom(width).c_str());

    return true;
}

inline auto printGuruMessage(WINDOW* window)
{
    setlocale(LC_ALL, "");

    NCURSES_ERROR_IF(not initscr());
    NCURSES_ERROR_IF(raw() == ERR);
    NCURSES_ERROR_IF(noecho() == ERR);
    NCURSES_ERROR_IF(curs_set(false) == ERR);
    NCURSES_ERROR_IF(refresh() == ERR);

    constexpr auto red_color_index = COLOR_RED;
    constexpr auto default_background_color = -1;
    NCURSES_ERROR_IF(start_color() == ERR);
    NCURSES_ERROR_IF(use_default_colors() == ERR);
    NCURSES_ERROR_IF(init_pair(red_color_index, COLOR_RED, default_background_color) == ERR);

    constexpr auto ignore_old_mask = nullptr;
    NCURSES_ERROR_IF(keypad(stdscr, true) == ERR);
    NCURSES_ERROR_IF(not(mousemask(BUTTON1_CLICKED, ignore_old_mask) & BUTTON1_CLICKED));

    constexpr auto line1 = "   Software Failure.    Press left mouse button to continue.   ";
    constexpr auto line2 = "              Guru Meditation #0000000C.48454C50               ";
    constexpr auto height = 4;
    const auto width = strlen(line1) + 2;
    constexpr auto red = COLOR_PAIR(red_color_index);
    NCURSES_ERROR_IF(not(window = newwin(height, width, 0, (COLS - width) / 2)));
    NCURSES_ERROR_IF(wattrset(window, A_BLINK | red) == ERR);
    NCURSES_ERROR_IF(not heavy_border(window) and box(window, 0, 0) == ERR);
    NCURSES_ERROR_IF(wattrset(window, A_BOLD | red) == ERR);
    NCURSES_ERROR_IF(mvwaddstr(window, 1, 1, line1) == ERR);
    NCURSES_ERROR_IF(mvwaddstr(window, 2, 1, line2) == ERR);
    NCURSES_ERROR_IF(wrefresh(window) == ERR);

    return true;
}

inline auto waitForLmb()
{
    int ch;
    MEVENT mevent{};

    while (not(mevent.bstate & BUTTON1_CLICKED))
    {
        NCURSES_ERROR_IF((ch = getch()) == ERR);
        NCURSES_ERROR_IF(ch == KEY_MOUSE and getmouse(&mevent) == ERR);
    }

    return true;
}

inline SigActionSignature(ignoreSignal)
{
    attrset(A_BLINK);
    mvaddstr(0, 0, "\u263a");
    refresh();
}

inline void printGuru(const Args& args)
{
    if (contains(args, "--force_guru") or chance(1337))
    {
        installSigaction(SIGTERM, ignoreSignal);
        WINDOW* window{};
        printGuruMessage(window) and waitForLmb();
        delwin(window);
        endwin();
    }
}
#else
inline void printGuru(const Args&) {}
#endif
