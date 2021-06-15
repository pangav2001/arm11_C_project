#include "ghost_movement.h"
#include "game_view.h"
#include <stdlib.h>

void calculate_ghost_movement(ghost_t *ghost) {
    //Always chooses the first that makes shorter
    int curr_distance = calculate_target_distance(ghost->x + ghost->dx, ghost->y + ghost->dy, ghost->target_x, ghost->target_y);
    int dx = ghost->dx;
    int dy = ghost->dy;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int new_distance = calculate_target_distance(ghost->x + i, ghost->y + j, ghost->target_x, ghost->target_y);
            if (new_distance < curr_distance && !(i == 0 && j == 0)) {
                curr_distance = new_distance;
                dx = i;
                dy = j;
            }
       
        }
    }
    ghost->dx = dx;
    ghost->dy = dy;
}

int calculate_target_distance(int curr_x, int curr_y, int target_x, int target_y) {
    return abs(target_x - curr_x) + abs(target_y - curr_y);
}

void move_ghost(game_t *game, map_t *map) {
    //update pos
    for (int i = 0; i < game->num_ghosts; i++) {
        calculate_ghost_movement(GHOST[i]);
        set_character(GHOST[i]->x, GHOST[i]->y, GHOST[i]->representation ,map);
        set_character(GHOST[i]->x - GHOST[i]->dx, GHOST[i]->y - GHOST[i]->dy, GHOST[i]->over, map);
    }

}