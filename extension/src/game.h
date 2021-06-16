#ifndef GAME_H
#define GAME_H

#include "pacman.h"
#include "ghosts.h"
#include "map.h"

typedef struct
{
    int num_ghosts;
    ghost_t **ghosts;
    pacman_t *pacman;
    int num_frames_ghost_reset; //-1 means ignore, we wait until 0, then we set ghost to chasing
    int lives;
    int points;
    int high_score;
    map_t *map;
} game_t;

int game_over(game_t *game);

#endif
