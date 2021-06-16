#ifndef MAP_H
#define MAP_H

#define MAP game->map

#include <ncurses.h>

typedef struct
{
    char**view;
    int max_x;
    int max_y;
    int pacman_start_offset; 
    int pellet_num;  
}map_t;

void print_view(WINDOW *window, game_t *game);

void set_char(int x, int y, char ch, map_t *map);

char get_char(int x, int y, map_t *map);

void create_map(game_t *game);

free_map(game_t *game);

#endif
