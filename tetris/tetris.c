//
// Created by arip on 28.10.22.
//

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"

int createIElement(int8_t pos, char **block)
{
    if (pos == 1)
    {
        for (int8_t i = 0; i < 2; i++)
        {
            for (int8_t j = 0; j < 8; j++)
                *(*(block + i) + j) = '#';
        }
    }
    else
    {
        for (int8_t i = 0; i < 8; i++)
        {
            for (int8_t j = 0; j < 2; j++)
                *(*(block + i) + j) = '#';
        }
    }

    return 0;
}

int createElement(int8_t type, int8_t pos, char **block)
{
    createIElement(pos, block);
    return 0;
}

int createMap(int rows, int cols, char **map)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (i == 0 || i == rows - 3 || j == 0 || j == cols - 32)
                *(*(map + i) + j) = '#';
            else
                *(*(map + i) + j) = ' ';
        }
    }
}

int renderTetris(int rows, int cols)
{
    int key, pos;
    char map[rows][cols];

    srand(time(NULL));
    createMap(rows, cols, map);

    do
    {
        clear();

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                printw("%c", map[i][j]);
            }
        }

        key = getch();
    } while (key != 27 || key != 260);

    return 0;
}
