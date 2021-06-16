#ifndef PACMAN_H
#define PACMAN_H

#include "game.h"

#define PACMAN_REPRESENTATION 'P'
#define PACMAN_WAIT 1
#define PACMAN game->pacman

void create_pacman(game_t *game);

void free_pacman(game_t *game);

void init_pacman(game_t *game);

void move_pacman(game_t *game, int dx, int dy);

#endif
