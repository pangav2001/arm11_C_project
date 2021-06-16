#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PELLETS 190
#define UI_HEIGHT 2

void print_view(WINDOW *window, game_t *game) {
    clear();
    
    // while (*view != NULL) {
    //     waddstr(window, *view++);
    //     waddstr(window, "\n");
    // }
    mvprintw(0, 1, "1UP\t\t HIGH SCORE");
    mvprintw(1, 1, "  %d\t\t%9d", game->points, game->high_score);

    int i = 0;
    for (; game->map->view[i]; i++) {
        mvprintw(i + UI_HEIGHT, 1, game->map->view[i]);
    }

    i++;

    for(int j = 0; j < game->lives - 1; j++)
    {
        mvprintw(i + UI_HEIGHT, j * 2, "%c", PACMAN_REPRESENTATION);
    }

    wrefresh(window);
    usleep(50000);
    
}

void set_char(int x, int y, char c, map_t *map) {
    map->view[y][x] = c;
}

char get_char(int x, int y, map_t *map) {
    return map->view[y][x];
}



static int get_max_x(char **view)
{
    return strlen(view[0]);
}

static int get_max_y(char **view)
{
    int y = 0;
    for (; view[y]; y++)
        ;
    return y;
}

void create_map(game_t *game)
{
    MAP = (map_t *)malloc(sizeof(map_t));
}

void free_map(game_t *game)
{
    free(MAP);
}

void init_map(game_t *game)
{
    char *view_test[24] = {
        "####################################### ",
        "# . . . . . . . . ### . . . . . . . . # ",
        "# O ### . ##### . ### . ##### . ### O # ",
        "# . . . . . . . . . . . . . . . . . . # ",
        "# . ### . # . ########### . # . ### . # ",
        "# . . . . # . . . ### . . . # . . . . # ",
        "####### . ##### . ### . ##### . ####### ",
        "      # . # . . . . . . . . # . #       ",
        "      # . # . ###-----### . # . #       ",
        "####### . # . #         # . # . #######\255",
        "        . . . #         # . . .         ",
        "####### . # . #         # . # . #######\255",
        "      # . # . ########### . # . #       ",
        "      # . # . . . . . . . . # . #       ",
        "####### . # . ########### . # . ####### ",
        "# . . . . . . . . ### . . . . . . . . # ",
        "# O ### . ##### . ### . ##### . ### O # ",
        "# . . # . . . . . . . . . . . . # . . # ",
        "### . # . # . ########### . # . # . ### ",
        "# . . . . # . . . ### . . . # . . . . # ",
        "# . ########### . ### . ########### . # ",
        "# . . . . . . . . . . . . . . . . . . # ",
        "####################################### ",
        NULL};

    MAP->view = calloc(24, sizeof(char *)); //
    for (int i = 0; i < 23; i++)
    {
        MAP->view[i] = strdup(view_test[i]);
    }
    MAP->view[24] = NULL;

    MAP->max_x = get_max_x(MAP->view);
    //Ignore the space at the end of the map
    MAP->max_y = get_max_y(MAP->view) - 1;

    MAP->pacman_start_offset = 6;

    MAP->pellet_num = MAX_PELLETS;
}
