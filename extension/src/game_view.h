#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <stdio.h>
#include <ncurses.h>
#include "actors.h"

#define DISTANCE_OUTSIDE 4

void print_view(WINDOW *window, game_t *game);

void set_character(int x, int y, char c, map_t *map);

char get_char(int x, int y, map_t *map);

void update_view(game_t *game, map_t *map);

#endif