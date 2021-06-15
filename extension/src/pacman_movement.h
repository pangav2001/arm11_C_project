#ifndef PACMAN_MOVEMENT_H
#define PACMAN_MOVEMENT_H

#include "actors.h"

int check_position_change(pacman_t *pacman, int dx, int dy, map_t *map);

void move_pacman(pacman_t *pacman, game_t *game, map_t *map);

#endif