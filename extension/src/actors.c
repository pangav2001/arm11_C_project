#include "actors.h"
#include "string.h"
#include "game_view.h"

#define GHOST game->ghosts

void crate_ghosts(game_t *game)
{
    for (int i = 0; i < game->num_ghosts; i++)
    {
        GHOST[i] = (ghost_t *)malloc(sizeof(ghost_t));
    }
}

void free_ghosts(game_t *game)
{
    for (int i = 0; i < game->num_ghosts; i++)
    {
        free(GHOST[i]);
    }
}

void init_ghosts(ghost_t **ghosts, int num_ghosts)
{
    for (int i = 0; i < num_ghosts; i++)
    {
        int mid_x = strlen(view[0]) / 2;
        int y = 0;
        for (; view[y]; y++)
            ;
        int mid_y = y / 2;

        //Change hard coding positions
        for (i = 0; i < num_ghosts; i++)
        {
            ghosts[i]->dx = 0;
            ghosts[i]->dy = 0;

            ghosts[i]->target_x = mid_x;
            ghosts[i]->target_y = mid_y - DISTANCE_OUTSIDE;

            ghosts[i]->mode = OFF;

            //To create a 3x3 box since max number of ghosts allowed is 9
            ghosts[i]->x = mid_x - 1 + (i % 3);
            ghosts[i]->x = mid_y - 1 + (i / 3);
        }
    }
}

void kill_ghost(ghost_t *ghost)
{
    ghost->mode = EATEN;

    int mid_x = strlen(view[0]) / 2;
    int y = 0;
    for (; view[y]; y++)
        ;
    int mid_y = y / 2;

    ghost->target_x = mid_x;
    ghost->target_y = mid_y;
}
void revive_ghost(ghost_t *ghost)
{
    ghost->mode = CHASING;
    int mid_x = strlen(view[0]) / 2;
    int y = 0;
    for (; view[y]; y++)
        ;
    int mid_y = y / 2;


    ghost->target_x = mid_x;
    ghost->target_y = mid_y - DISTANCE_OUTSIDE;

}