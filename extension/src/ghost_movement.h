#ifndef GHOST_MOVEMENT_H
#define GHOST_MOVEMENT_H

#include "actors.h"

void calculate_ghost_movement(ghost_t *ghost, game_t *game);

int calculate_target_distance(int curr_x, int curr_y, int target_x, int target_y);

void move_ghost(game_t *game, map_t *map);

void update_ghost_targets(game_t *game, map_t *map);

int check_pacman_collision(game_t *game);
#endif