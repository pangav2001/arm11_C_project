#include "actors.h"

void init_game(game_t *game) {
    game->lives = 3;
    game->num_frames_ghost_reset = -1;

    game->num_ghosts = 4;
    game->points = 0;
    //game->ghosts = ;


}

void init_pacman(pacman_t *pacman) {
    pacman->dx = 0;
    pacman->dy = 0;

    //check pos
    pacman->x = 13; 
    pacman->y = 19;
}

void kill_pacman(pacman_t *pacman, game_t *game) {
    game->lives -= 1;
    init_pacman(pacman);
}