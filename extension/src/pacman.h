#ifndef PACMAN_H
#define PACMAN_H

#define PACMAN_REPRESENTATION 'P'
#define PACMAN_WAIT 1
#define PACMAN game->pacman

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int pacman_wait;
} pacman_t;

void create_pacman(game_t *game);

void free_pacman(game_t *game);

void init_pacman(game_t *game);

void move_pacman(game_t *game, int dx, int dy);

#endif
