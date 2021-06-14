#include "pacman_movement.h"
#include "game_view.h"
#include "actors.h"

int check_position_change(pacman *pacman, int dx, int dy)
{
    int new_x = pacman->x + pacman->dx;
    int new_y = pacman->y + pacman->dy;

    return get_char(new_x, new_y) != '#' && get_char(new_x, new_y) != '-';
}

void check_collision(pacman *pacman, game *game)
{
    int new_x = pacman->x + pacman->dx;
    int new_y = pacman->y + pacman->dy;

    char in_way = get_char(new_x, new_y);

    switch (in_way)
    {
    case '-':
    case '#':
        //Stop pacman
        pacman->dx = 0;
        pacman->dy = 0;
        break;
    case 'G':
        for (int i = 0; i < game->num_ghosts; i++)
        {
            if (game->ghosts[i].x == new_x && game->ghosts[i].y == new_y)
            {
                switch (game->ghosts[i].mode)
                {
                case CHASING:
                    //TODO
                    break;
                case CHASED:
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

        //Power pellet is worth 40 points more than pellet
        game->points += 40;
    case '.':
        //Power pellet is worth 10 points
        game->points += 10;
    default:
        pacman->x += pacman->dx;
        pacman->y += pacman->dy;
        break;
    };
}