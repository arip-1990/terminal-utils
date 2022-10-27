#include <ncurses.h>
#include "pharm.h"

int main() {
    int rows, cols, key, pos;

    initscr();
    curs_set(0);
    keypad(stdscr, true);
    getmaxyx(stdscr, rows, cols);

    do {
        clear();
        if (key == 10) {
            choose_service(rows, cols);
            clear();
        }

        mvprintw(1, 2, ">> Copy server log file");
        mvprintw(rows - 2, 2, "Press key: %d", key);
    } while ((key = getch()) != 27);

    endwin();
    return 0;
}
