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

#endif
