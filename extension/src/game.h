#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "ghosts.h"
#include "pacman.h"
#include "map.h"

#define NEXT_X(ACTOR) (ACTOR->x + ACTOR->dx)
#define NEXT_Y(ACTOR) (ACTOR->x + ACTOR->dy)
#define PREV_X(ACTOR) (ACTOR->x - ACTOR->dx)
#define PREV_Y(ACTOR) (ACTOR->x - ACTOR->dy)
#define NOT_MOVING(ACTOR) ((ACTOR->dx == 0) && (ACTOR->dy == 0))


int game_over(game_t *game);

#endif
