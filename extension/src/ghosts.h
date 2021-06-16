#ifndef GHOSTS_H
#define GHOSTS_H

typedef enum
{
    CHASING,
    SCATTER,
    FRIGHTENED,
    EATEN,
    OFF
} Ghost_Mode_t;

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int target_x;
    int target_y;
    int ghost_wait; //when 0 can move, otherwise number of frames until can move
    char over; //character ghost is over to place back
    Ghost_Mode_t mode;
} ghost_t;

#endif
