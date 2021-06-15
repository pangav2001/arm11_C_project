#include "ghost_movement.h"
#include "game_view.h"

void calculate_ghost_movement(ghost_t *ghost) {

}

int calculate_target_distance(int curr_x, int curr_y, int target_x, int target_y) {
    return 0;
}

void move_ghost(game_t *game, char **view) {
    //update pos

    //update view
    for (int i = 0; i < game->num_ghosts; i++) {
        set_character(game->ghosts[i]->x, game->ghosts[i]->y,game->ghosts[i]->representation ,view);
    }

}