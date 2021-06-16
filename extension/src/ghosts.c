#include <stdlib.h>
#include "ghosts.h"

void create_ghosts(game_t *game) {
    
    GHOSTS = (ghost_t **)malloc(game->num_ghosts * sizeof(ghost_t *));
    
    for (int i = 0; i < game->num_ghosts; i++)
    {
        GHOSTS[i] = (ghost_t *)malloc(sizeof(ghost_t));
        GHOSTS[i]->over = ' ';
        GHOSTS[i]->ghost_wait = i * GHOST_START_DELAY;
    }
}

void free_ghosts(game_t *game) {
    for (int i = 0; i < game->num_ghosts; i++)
    {
        free(GHOSTS[i]);
    }
    free(GHOSTS);
}

void init_ghost(game_t *game , ghost_t *ghost) {
    int mid_x = game->map->max_x / 2;
    int mid_y = game->map->max_y / 2;
    
    ghost->dx = 0;
    ghost->dy = 0;

    ghost->target_x = mid_x;
    ghost->target_y = mid_y - DISTANCE_OUTSIDE;

    //Do we need the 3/3 box since delay in starting

}

void init_all_ghosts(game_t *game) {
    for (int i = 0; i < game->num_ghosts; i++) {
        init_ghost(game,GHOSTS[i]);
    }
}

void update_ghosts_targets(game_t *game) {

}

//Checks new movement would be valid
int check_ghost_position(game_t *game, ghost_t *ghost, int dx, int dy) {
    int new_x = ghost->x + dx;
    int new_y = ghost->y + dy;

    return get_char(new_x, new_y, game->map) != '#' && get_char(new_x, new_y, game->map) != 'G';
}

int diagonal(int dx, int dy) {
    return abs(dx) == 1 && abs(dy) == 1;
}

void move_ghosts(game_t *game) {

}