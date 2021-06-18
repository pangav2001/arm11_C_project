#ifndef MAP_H
#define MAP_H

#define MAP game->map

#include <ncurses.h>

void print_char_colour(Game_Constructs_t object, int x, int y, unsigned char c, int frightened_mode);

void print_view(WINDOW *window, game_t *game);

void set_char(int x, int y, char ch, map_t *map);

char get_char(int x, int y, map_t *map);

void create_map(game_t *game);

void init_map(game_t *game);

void free_map(game_t *game);

#endif
