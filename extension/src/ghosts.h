#ifndef GHOSTS_H
#define GHOSTS_H

#include "game.h"

#define GHOSTS game->ghosts
#define GHOST_START_DELAY 20
#define DISTANCE_OUTSIDE 3

typedef enum
{
    CHASING,
    SCATTER,
    FRIGHTENED,
    EATEN,
    OFF
} Ghost_Mode_t;

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int target_x;
    int target_y;
    int ghost_wait; //when 0 can move, otherwise number of frames until can move
    char over; //character ghost is over to place back
    Ghost_Mode_t mode;
} ghost_t;

void create_ghosts(game_t *game);

void free_ghosts(game_t *game);

void init_ghost(game_t *game , ghost_t *ghost);

void init_all_ghosts(game_t *game);

void move_ghosts(game_t *game);

#endif
