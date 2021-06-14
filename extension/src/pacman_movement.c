#include "pacman_movement.h"
#include "game_view.h"



int check_position_change(pacman *pacman, int dx, int dy) {
    return get_char(pacman->x + dx, pacman->y + dy) != '#';
}

void check_collision(pacman *pacman) {
    char in_way = get_char(pacman->x + pacman->dx, pacman->y + pacman->dy);

    switch (in_way) {
        case '.':
            //increament and update
            break;
        case '#':
            //update to 0,0
            break;
        case 'O':
            //blue shit
            break;
        case 'G':
            //maybe die maybe success
            break;
        default:
            break;
    };
}