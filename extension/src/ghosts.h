#ifndef GHOSTS_H
#define GHOSTS_H

#include "game.h"

#define GHOSTS game->ghosts
#define GHOST_START_DELAY 20
#define DISTANCE_OUTSIDE 3
#define GHOST_REPRESENTATION 'G'
#define GHOST_WAIT 2

void create_ghosts(game_t *game);

void free_ghosts(game_t *game);

void set_ghost_mode(ghost_t *ghost, Ghost_Mode_t mode);

void init_ghost(game_t *game , ghost_t *ghost);

void init_all_ghosts(game_t *game);

void move_ghosts(game_t *game);

#endif
