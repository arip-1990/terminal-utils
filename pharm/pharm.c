//
// Created by arip on 27.10.22.
//

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "pharm.h"

int render_menu(int pos, char *service_name)
{
    clear();
    mvprintw(1, 2, "Choose a service:");

    switch (pos) {
        case 1:
            mvprintw(3, 2, "   api-php-fpm");
            mvprintw(5, 2, ">> api-cheduler");
            mvprintw(7, 2, "   api-worker");
            mvprintw(9, 2, "   api-subscribe");

            strcpy(service_name, "api-cheduler");
            break;
        case 2:
            mvprintw(3, 2, "   api-php-fpm");
            mvprintw(5, 2, "   api-cheduler");
            mvprintw(7, 2, ">> api-worker");
            mvprintw(9, 2, "   api-subscribe");

            strcpy(service_name, "api-worker");
            break;
        case 3:
            mvprintw(3, 2, "   api-php-fpm");
            mvprintw(5, 2, "   api-cheduler");
            mvprintw(7, 2, "   api-worker");
            mvprintw(9, 2, ">> api-subscribe");

            strcpy(service_name, "api-subscribe");
            break;
        default:
            mvprintw(3, 2, ">> api-php-fpm");
            mvprintw(5, 2, "   api-cheduler");
            mvprintw(7, 2, "   api-worker");
            mvprintw(9, 2, "   api-subscribe");

            strcpy(service_name, "api-php-fpm");
    }
}

int copy_log_file(char *service_name)
{
    char command[255] = "ssh arip@185.46.10.253 'docker cp $(docker ps -f name=pharm_";

    strcat(command, service_name);
    strcat(command, " --format {{.Names}}):/app/storage/logs/laravel.log /home/arip/");
    strcat(command, service_name);
    strcat(command, ".log'");

    system(command);

    strcpy(command, "scp arip@185.46.10.253:./");
    strcat(command, service_name);
    strcat(command, ".log /home/arip/Documents");

    system(command);
}

int choose_service(int rows, int cols)
{
    int key, pos = 0;
    char service_name[16];

    do {
        if (key == 10) {
            mvprintw(rows - 2, 2, "Service \"%s\": log file is being copied...", service_name);
            refresh();
            copy_log_file(service_name);
        } else if (key == 258) {
            pos++;
            if (pos > 3) pos = 0;
        } else if (key == 259) {
            pos--;
            if (pos < 0) pos = 3;
        }

        render_menu(pos, service_name);
    } while ((key = getch()) != 27);

    return 0;
}
