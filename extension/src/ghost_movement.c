#include "ghost_movement.h"
#include "game_view.h"
#include "actors.h"
#include <time.h>
#include <stdlib.h>

int check_ghost_position(ghost_t *ghost, int dx, int dy, game_t *game)
{
    int new_x = ghost->x + dx;
    int new_y = ghost->y + dy;

    return get_char(new_x, new_y, game->map) != '#' && get_char(new_x, new_y, game->map) != 'G';
}

int check_pacman_collision(game_t *game)
{
    for (int i = 0; i < game->num_ghosts; i++)
    {
        if (get_char(game->ghosts[i]->x, game->ghosts[i]->y, game->map) == 'P')
        {
            set_character(game->pacman->x, game->pacman->y, ' ', game->map);
            kill_pacman(game->pacman, game, game->map->view);
            init_ghosts(game->ghosts, game->num_ghosts, game->map);
            // game->ghosts[i]->over = ' ';
            return 1;
        }
    }
    return 0;
}

int diaganol_movement(int dx, int dy)
{
    return abs(dx) == 1 && abs(dy) == 1;
}

void calculate_ghost_movement(ghost_t *ghost, game_t *game)
{
    //What happens when we are at the target?
    int curr_distance = calculate_target_distance(ghost->x + ghost->dx, ghost->y + ghost->dy, ghost->target_x, ghost->target_y);
    int dx = ghost->dx;
    int dy = ghost->dy;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int new_distance = calculate_target_distance(ghost->x + i, ghost->y + j, ghost->target_x, ghost->target_y);
            if (new_distance < curr_distance && !(i == 0 && j == 0) && check_ghost_position(ghost, i, j, game) && !diaganol_movement(i, j))
            {
                curr_distance = new_distance;
                dx = i;
                dy = j;
            }
        }
    }
    int new_x = ghost->x + dx;
    int new_y = ghost->y + dy;
    char in_way = get_char(new_x, new_y, game->map);

    //where do we check for collision of pacman and ghost??
    switch (in_way)
    {
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
        ghost->dx = dx;
        ghost->dy = dy;
        ghost->x = ghost->x + dx;
        ghost->y = ghost->y + dy;
    }
}

int calculate_target_distance(int curr_x, int curr_y, int target_x, int target_y)
{
    return abs(target_x - curr_x) + abs(target_y - curr_y);
}

void move_ghost(game_t *game, map_t *map)
{
    //update pos
    for (int i = 0; i < game->num_ghosts; i++)
    {
        // //causing screen to disappear at the moment
        if (GHOST[i]->ghost_wait == 0)
        {
            GHOST[i]->ghost_wait = GHOST_WAIT;
            calculate_ghost_movement(GHOST[i], game);
            if (!(GHOST[i]->dx == 0 && GHOST[i]->dy == 0))
            {
                //put back over character
                set_character(GHOST[i]->x - GHOST[i]->dx, GHOST[i]->y - GHOST[i]->dy, GHOST[i]->over == game->pacman->representation ? ' ' : GHOST[i]->over, map);
                GHOST[i]->over = get_char(GHOST[i]->x, GHOST[i]->y, map);
                set_character(GHOST[i]->x, GHOST[i]->y, GHOST[i]->representation, map);
            }
        }
        else
        {
            GHOST[i]->ghost_wait--;
        }
    }
}

void update_ghost_targets(game_t *game, map_t *map)
{
    //srand(time(NULL));

    for (int i = 0; i < game->num_ghosts; i++)
    {
        //set targets random for now
        // int x = rand() % (map->max_x - 1);
        // int y = rand() % (map->max_y - 1);
        // GHOST[i]->target_x = x;
        // GHOST[i]->target_y = y;

        switch (GHOST[i]->mode)
        {
        case OFF:
            if (GHOST[i]->target_x == GHOST[i]->x && GHOST[i]->target_y == GHOST[i]->y)
            {
                GHOST[i]->mode = CHASING;
            }
            break;
        case CHASING:
            GHOST[i]->target_x = game->pacman->x;
            GHOST[i]->target_y = game->pacman->y;
            break;
        default:
            GHOST[i]->target_x = game->pacman->x;
            GHOST[i]->target_y = game->pacman->y;
        }
    }
}