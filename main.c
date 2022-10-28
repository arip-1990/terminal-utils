#include <ncurses.h>
#include "pharm/pharm.h"
#include "./tetris/tetris.h"

int main() {
    int rows, cols, key, pos;

    initscr();
    curs_set(0);
    keypad(stdscr, true);
    getmaxyx(stdscr, rows, cols);

    do {
        clear();
        if (key == 10) {
            if (pos == 0) choose_service(rows, cols);
            else renderTetris(rows, cols);

            clear();
        } else if (key == 258) {
            pos++;
            if (pos > 1) pos = 0;
        } else if (key == 259) {
            pos--;
            if (pos < 0) pos = 1;
        }

        if (pos == 0) {
            mvprintw(1, 2, ">> Copy server log file");
            mvprintw(3, 2, "   Tetris");
        } else {
            mvprintw(1, 2, "   Copy server log file");
            mvprintw(3, 2, ">> Tetris");
        }

        mvprintw(rows - 2, 2, "Press key: %d", key);
    } while ((key = getch()) != 27);

    endwin();
    return 0;
}
