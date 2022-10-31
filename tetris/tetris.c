//
// Created by arip on 28.10.22.
//

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "tetris.h"

int createIFigure(int pos, char **block)
{
    if (pos)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                if (j > 2 && j < 5)
                    block[i][j] = '#';
                else
                    block[i][j] = ' ';
            }
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                if (i > 2 && i < 5)
                    block[i][j] = '#';
                else
                    block[i][j] = ' ';
            }
        }
    }

    return 0;
}

int createFigure(int type, int pos, char **block)
{
    createIFigure(pos, block);
    return 0;
}

int createMap(int rows, int cols, char **map)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (i == 0 || i == rows - 3 || j == 0 || j == cols - 32)
                map[i][j] = '#';
            else
                map[i][j] = ' ';
        }
    }
}

int copyFigure(char **block1, char **block2)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 16; j++)
            block2[i][j] = block1[i][j];
    }
}

int renderFigure(int key, int cols, char **map, char **block)
{
    unsigned int posY = 0, posX = cols / 2;

    if (key == 258)
    {
        if (map[posY + 2][posX] == ' ')
            posY += 2;
        else if (map[posY + 1][posX] == ' ')
            posY++;
        else
            return 1;
    }
    else if (key == 261)
    {
        if (map[posY][posX + 1] == ' ')
            posX++;
    }
    else if (key == 260)
    {
        if (map[posY][posX - 1] == ' ')
            posX--;
    }
    else
    {
        if (map[posY + 1][posX] == ' ')
            posY++;
        else
            return 1;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            mvprintw(posY + i, posX + j, "%c", block[i][j]);
        }
    }

    return 0;
}

int renderTetris(int rows, int cols)
{
    int key = 0, pos = 0, start = 0, end = 0;
    char *map[rows];
    char *block1[8], *block2[8];

    for (int i = 0; i < rows; i++)
        map[i] = malloc(cols * sizeof(char));

    for (int i = 0; i < 16; i++)
    {
        block1[i] = malloc(8 * sizeof(char));
        block2[i] = malloc(8 * sizeof(char));
    }

    // srand(time(NULL));

    createMap(rows, cols, map);
    createFigure(0, 0, block1);

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

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                mvprintw(i + 4, j + (cols - 22), "%c", block1[i][j]);
            }
        }

        if (start)
        {
            end = renderFigure(key, cols, map, block2);
        }

        if (start == 0 || end)
        {
            copyFigure(block1, block2);
            createFigure(0, 0, block1);
        }

        mvprintw(rows - 2, 2, "Press key: %d", key);

        start = 1;
        key = getch();
    } while (key != 27);

    for (int i = 0; i < rows; i++)
        free(map[i]);

    for (int i = 0; i < 8; i++)
    {
        free(block1[i]);
        free(block2[i]);
    }

    return 0;
}
