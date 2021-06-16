#include "game.h"

void create_pacman(game_t *game)
{
    PACMAN = (pacman_t *)malloc(sizeof(pacman_t));
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
    set_character(PACMAN->x, PACMAN->y, ' ', game->map);
    init_pacman(game);
}

int valid_move_pacman(game_t *game, int dx, int dy)
{
    int new_x = PACMAN->x + dx;
    int new_y = PACMAN->y + dy;
    
    return get_char(new_x, new_y, game->map) != '#' && get_char(new_x, new_y, game->map) != '-' && get_char(new_x, new_y, game->map) != '\255';
}

void move_pacman(game_t *game, int dx, int dy)
{
    
    if (check_position_change(PACMAN, dx, dy, game)) {
        PACMAN->dx = dx;
        PACMAN->dy = dy;
    }

    if (PACMAN->pacman_wait != 0) {
        pacman->pacman_wait --;
        return;
    }
    PACMAN->pacman_wait = PACMAN_WAIT;


    int new_x = pacman->x + pacman->dx;
    int new_y = pacman->y + pacman->dy;

    char in_way = get_char(new_x, new_y, game->map);

    switch (in_way)
    {
    case '\255':
    case '-':
    case '#':
        //Stop pacman
        pacman->dx = 0;
        pacman->dy = 0;
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
                    //TODO
                    break;
                case FRIGHTENED:
                    //TODO
                    break;
                default:
                    //TODO
                    break;
                }
                break;
            }
        }
        break;
    case 'O':
        //TODO Set all ghosts to frightened mode
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
        //Power pellet is worth 10 points
        game->points += 10;
    default:
        if (pacman->x <= 0)
        {
            pacman->x = MAP->max_x - 1;
        }
        else if (pacman->x >= MAP->max_x)
        {
            pacman->x = 1;
        }
        else
        {
            pacman->x = new_x;
            pacman->y = new_y;
        }
        break;
    };

    //clear pacman prev
    set_character(pacman->x - pacman->dx, pacman->y - pacman->dy, ' ', MAP);
}

