#include <stdlib.h>
#include "ghosts.h"
#include <assert.h>

void create_ghosts(game_t *game) {
    
    GHOSTS = (ghost_t **)malloc(game->num_ghosts * sizeof(ghost_t *));
    
    assert(game->num_ghosts <= 4);
    for (int i = 0; i < game->num_ghosts; i++)
    {
        GHOSTS[i] = (ghost_t *)malloc(sizeof(ghost_t));
        GHOSTS[i]->ghost_name = i + 1; //starts at 1
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

    ghost->mode = OFF;
    
    ghost->dx = 0;
    ghost->dy = 0;

    ghost->x = mid_x;
    ghost->y = mid_y;

    ghost->over = ' ';

    ghost->target_x = mid_x;
    ghost->target_y = mid_y - 4;

    //Do we need the 3/3 box since delay in starting

}

void init_all_ghosts(game_t *game) {
    for (int i = 0; i < game->num_ghosts; i++) {
        init_ghost(game,GHOSTS[i]);
        GHOSTS[i]->ghost_wait = i * GHOST_START_DELAY;
    }
}

void update_ghosts_targets(game_t *game) {
    for (int i = 0; i < game->num_ghosts; i++) {
        switch (GHOSTS[i]->mode) {
            case OFF:
                if (GHOSTS[i]->target_x == GHOSTS[i]->x && GHOSTS[i]->target_y == GHOSTS[i]->y) {
                    GHOSTS[i]->mode = CHASING;
                }
                break;
            case FRIGHTENED:
                if (game->num_frames_ghost_reset == 0) {
                    GHOSTS[i]->mode = CHASING;
                } else {
                //bit dodgy
                    GHOSTS[i]->target_x = game->map->max_x - PACMAN->x;
                    GHOSTS[i]->target_y = game->map->max_y - PACMAN->y;
                    game->num_frames_ghost_reset --;
                }
                break;
            // implement rest
            default:
                GHOSTS[i]->target_x = PACMAN->x;
                GHOSTS[i]->target_y = PACMAN->y;
        }
    }
}

//Checks new movement would be valid
int check_ghost_position(game_t *game, ghost_t *ghost, int dx, int dy) {
    int new_x = ghost->x + dx;
    int new_y = ghost->y + dy;

    return get_char(new_x, new_y, game->map) != '#' && get_char(new_x, new_y, game->map) != 'G' && get_char(new_x, new_y, game->map) != 'b';
}

int diagonal(int dx, int dy) {
    return abs(dx) == 1 && abs(dy) == 1;
}

int target_distance(int curr_x, int curr_y, int target_x, int target_y) {
    return abs(target_x - curr_x) + abs(target_y - curr_y);

}

void calculate_ghost_movement(game_t *game, ghost_t *ghost) {
    int curr_path_distance = target_distance(NEXT_X(ghost), NEXT_Y(ghost),ghost->target_x, ghost->target_y);

    //get best movement ignoring curr path
    //will this always work?
    int new_dx;
    int new_dy;
    int new_distance = game->map->max_x + game->map->max_y;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int distance = target_distance(ghost->x + i, ghost->y + j, ghost->target_x, ghost->target_y);
            //stop ghost going over eachother
            if (distance < new_distance && !diagonal(i,j) && (i != 0 || j != 0) && check_ghost_position(game, ghost, i, j)) {
                new_dx = i;
                new_dy = j;
                new_distance = distance;
            }
        }
    }

    //choose current path or change
    if (curr_path_distance < new_distance && check_ghost_position(game, ghost, ghost->dx, ghost->dy)) {
        new_dx = ghost->dx;
        new_dy = ghost->dy;
    }

    //Case where we want to stay maybe set new_dx to -2 check if -2 then set to 0

    char in_way = get_char(ghost->x + new_dx, ghost->y + new_dy, game->map);

    switch (in_way) {
        case 'b':
        case '#':
        case 'G':
            ghost->dx = 0;
            ghost->dy = 0;
            break;
        case '-':
            if (!(ghost->mode == OFF || ghost->mode == EATEN))
            {
                ghost->dx = 0;
                ghost->dy = 0;
                break;
            }
        default:
            ghost->dx = new_dx;
            ghost->dy = new_dy;
            ghost->x = NEXT_X(ghost);
            ghost->y = NEXT_Y(ghost);
    }
}

void move_ghosts(game_t *game) {
    for (int i = 0; i < game->num_ghosts; i++) {
        if (GHOSTS[i]->ghost_wait == 0) {
            GHOSTS[i]->ghost_wait = GHOST_WAIT;

            calculate_ghost_movement(game, GHOSTS[i]);

            if (!NOT_MOVING(GHOSTS[i])) {
                set_char(PREV_X(GHOSTS[i]), PREV_Y(GHOSTS[i]), GHOSTS[i]->over, game->map);
                GHOSTS[i]->over = get_char(GHOSTS[i]->x, GHOSTS[i]->y, game->map);
                set_char(GHOSTS[i]->x, GHOSTS[i]->y, GHOST_REPRESENTATION, game->map);
            }
        } else {
            GHOSTS[i]->ghost_wait --;            
        }
    }
    update_ghosts_targets(game);


}