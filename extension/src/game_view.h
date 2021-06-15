#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <stdio.h>
#include <ncurses.h>
#include "actors.h"

#define DISTANCE_OUTSIDE 3

void print_view(WINDOW *window, char **view, game_t *game);

void set_character(int x, int y, char c, char **view);

char get_char(int x, int y, char **view);

void update_view(game_t *game, char **view);

#endif