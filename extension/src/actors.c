#include <string.h>
#include "game_view.h"
#include "actors.h"
#include <stdlib.h>

void crate_ghosts(game_t *game)
{
    GHOST = (ghost_t **)malloc(game->num_ghosts * sizeof(ghost_t *));
    for (int i = 0; i < game->num_ghosts; i++)
    {
        GHOST[i] = (ghost_t *)malloc(sizeof(ghost_t));
        GHOST[i]->representation = 'G';
        GHOST[i]->over = ' ';
    }
}

void free_ghosts(game_t *game)
{
    for (int i = 0; i < game->num_ghosts; i++)
    {
        free(GHOST[i]);
    }
    free(game->ghosts);
}


void init_ghosts(ghost_t **ghosts, int num_ghosts, map_t *map)
{
    for (int i = 0; i < num_ghosts; i++)
    {
        int mid_x = map->max_x / 2;
        int mid_y = map->max_y / 2;

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
            ghosts[i]->y = mid_y - 2 + (i / 3);
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

void init_game(game_t *game, pacman_t *pacman)
{
    game->lives = 3;
    game->num_frames_ghost_reset = -1;

    game->num_ghosts = 4;
    game->points = 0;
    game->high_score = 10700;
    //game->ghosts = ;

    game->pacman = pacman;
}

void init_pacman(pacman_t *pacman, map_t *map)
{
    pacman->representation = 'P';

    pacman->dx = -1;
    pacman->dy = 0;

    //check pos
    pacman->x = map->max_x / 2;
    pacman->y = map->max_y / 2 + map->pacman_start_offset;
}

void kill_pacman(pacman_t *pacman, game_t *game, char **view)
{
    game->lives -= 1;
    init_pacman(pacman, game->map);
}

static int get_max_x(char **view)
{
    return strlen(view[0]);
}

static int get_max_y(char **view)
{
    int y = 0;
    for (; view[y]; y++)
        ;
    return y;
}

void init_map(game_t *game)
{
    game->map = (map_t *)malloc(sizeof(map_t));

    char *view_test[24] = {
        "#######################################",
        "# . . . . . . . . ### . . . . . . . . #",
        "# O ### . ##### . ### . ##### . ### O #",
        "# . . . . . . . . . . . . . . . . . . #",
        "# . ### . # . ########### . # . ### . #",
        "# . . . . # . . . ### . . . # . . . . #",
        "####### . ##### . ### . ##### . #######",
        "      # . # . . . . . . . . # . #      ",
        "      # . # . ###-----### . # . #      ",
        "####### . # . #         # . # . #######",
        "        . . . #         # . . .        ",
        "####### . # . #         # . # . #######",
        "      # . # . ########### . # . #      ",
        "      # . # . . . . . . . . # . #      ",
        "####### . # . ########### . # . #######",
        "# . . . . . . . . ### . . . . . . . . #",
        "# O ### . ##### . ### . ##### . ### O #",
        "# . . # . . . . . . . . . . . . # . . #",
        "### . # . # . ########### . # . # . ###",
        "# . . . . # . . . ### . . . # . . . . #",
        "# . ########### . ### . ########### . #",
        "# . . . . . . . . . . . . . . . . . . #",
        "#######################################",
        NULL};

    game->map->view = calloc(24, sizeof(char *)); //
    for (int i = 0; i < 23; i++)
    {
        game->map->view[i] = strdup(view_test[i]);
    }
    game->map->view[24] = NULL;

    game->map->max_x = get_max_x(game->map->view);
    game->map->max_y = get_max_y(game->map->view);

    game->map->pacman_start_offset = 6;
}