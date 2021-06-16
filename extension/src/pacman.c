#include "pacman.h"
#include <stdlib.h>

void create_pacman(game_t *game)
{
    PACMAN = (pacman_t *)malloc(sizeof(pacman_t));
}

void free_pacman(game_t *game)
{
    free(PACMAN);
}

void init_pacman(game_t *game)
{
    PACMAN->dx = -1;
    PACMAN->dy = 0;
    PACMAN->pacman_wait = PACMAN_WAIT;

    //check pos
    PACMAN->x = game->map->max_x / 2;
    PACMAN->y = game->map->max_y / 2 + game->map->pacman_start_offset;
}

void kill_pacman(game_t *game)
{
    game->lives -= 1;
    set_char(PACMAN->x, PACMAN->y, ' ', game->map);
    init_pacman(game);
    init_all_ghosts(game);
}

static int valid_move_pacman(game_t *game, int dx, int dy)
{
    int new_x = PACMAN->x + dx;
    int new_y = PACMAN->y + dy;

    return get_char(new_x, new_y, game->map) != '#' && get_char(new_x, new_y, game->map) != '-' && get_char(new_x, new_y, game->map) != '\255';
}

void move_pacman(game_t *game, int dx, int dy)
{

    if (valid_move_pacman(game, dx, dy))
    {
        PACMAN->dx = dx;
        PACMAN->dy = dy;
    }

    if (PACMAN->pacman_wait != 0)
    {
        PACMAN->pacman_wait--;
        return;
    }
    PACMAN->pacman_wait = PACMAN_WAIT;

    int new_x = PACMAN->x + PACMAN->dx;
    int new_y = PACMAN->y + PACMAN->dy;

    char in_way = get_char(new_x, new_y, game->map);

    switch (in_way)
    {
    case '\255':
    case '-':
    case '#':
        //Stop pacman
        PACMAN->dx = 0;
        PACMAN->dy = 0;
        break;
    case 'G':
        for (int i = 0; i < game->num_ghosts; i++)
        {
            if (GHOSTS[i]->x == new_x && GHOSTS[i]->y == new_y)
            {
                switch (GHOSTS[i]->mode)
                {
                case SCATTER:
                case CHASING:
                    game->ghosts[i]->over = ' ';
                    kill_pacman(game);
                    return;
                    break;
                case FRIGHTENED:
                    //TODO
                    break;
                default:
                    break;
                }
                break;
            }
        }
        break;
    case 'O':
        game->num_frames_ghost_reset = 3000; //might need to change
        for (int i = 0; i < game->num_ghosts; i++)
        {
            if (GHOSTS[i]->mode == CHASING || GHOSTS[i]->mode == SCATTER)
            {
                GHOSTS[i]->mode = FRIGHTENED;
            }
        }

        //Power pellet is worth 40 points more than pellet
        game->points += 40;
    case '.':
        //Normal pellet is worth 10 points
        game->points += 10;
        MAP->pellet_num--;
    default:
        if (PACMAN->x <= 0)
        {
            PACMAN->x = MAP->max_x - 1;
            set_char(0, PACMAN->y, ' ', MAP);
        }
        else if (PACMAN->x >= MAP->max_x)
        {
            PACMAN->x = 1;
            set_char(MAP->max_x, PACMAN->y, ' ', MAP);
        }
        else
        {
            PACMAN->x = new_x;
            PACMAN->y = new_y;
            set_char(PACMAN->x - PACMAN->dx, PACMAN->y - PACMAN->dy, ' ', MAP);
        }
        break;
    };

    set_char(PACMAN->x, PACMAN->y, PACMAN_REPRESENTATION, MAP);
}
