//
// Created by arip on 28.10.22.
//

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"

int renderTetris(int rows, int cols)
{
    int key, pos;
    char map[rows][cols];

//    srand(time(NULL));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == 0 || i == rows - 3 || j == 0 || j == cols - 32) map[i][j] = '#';
            else map[i][j] = ' ';
        }
    }

    do {
        clear();


        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                printw("%c", map[i][j]);
            }
        }
    } while ((key = getch()) != 27);

    return 0;
}
