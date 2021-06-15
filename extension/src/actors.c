#include <string.h>
#include "game_view.h"
#include "actors.h"
#include <stdlib.h>



#define GHOST game->ghosts

void crate_ghosts(game_t *game)
{
    for (int i = 0; i < game->num_ghosts; i++)
    {
        GHOST[i] = (ghost_t *)malloc(sizeof(ghost_t));
        GHOST[i]->representation = 'G';
    }
}

void free_ghosts(game_t *game)
{
    for (int i = 0; i < game->num_ghosts; i++)
    {
        free(GHOST[i]);
    }
}

int get_mid_x(char **view){
    return strlen(view[0]) / 2;
}

int get_mid_y(char **view) {
    int y = 0;
    for (; view[y]; y++)
        ;
    return y / 2;
}

void init_ghosts(ghost_t **ghosts, int num_ghosts, char **view)
{
    for (int i = 0; i < num_ghosts; i++)
    {
        // int mid_x = strlen(view[0]) / 2;
        // int y = 0;
        // for (; view[y]; y++)
        //     ;
        // int mid_y = y / 2;
        int mid_x = get_mid_x(view);
        int mid_y = get_mid_y(view);

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

void kill_ghost(ghost_t *ghost, char **view)
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
void revive_ghost(ghost_t *ghost, char **view)
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

void init_game(game_t *game, pacman_t *pacman) {
    game->lives = 3;
    game->num_frames_ghost_reset = -1;

    game->num_ghosts = 4;
    game->points = 0;
    //game->ghosts = ;

    game->pacman = pacman;


}

void init_pacman(pacman_t *pacman, char **view) {
    pacman->representation = 'P';
    
    pacman->dx = 0;
    pacman->dy = 0;

    //check pos
    pacman->x = get_mid_x(view); 
    pacman->y = get_mid_y(view) + 6;
}

void kill_pacman(pacman_t *pacman, game_t *game, char **view) {
    game->lives -= 1;
    init_pacman(pacman, view);
}