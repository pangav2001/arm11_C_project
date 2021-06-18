#ifndef TYPES_H
#define TYPES_H

#define GHOST_REPRESENTATION 'M'
#define PACMAN_REPRESENTATION 'P'

typedef enum
{
    CHASING,
    SCATTER,
    FRIGHTENED,
    EATEN,
    OFF
} Ghost_Mode_t;

typedef enum
{
    INKY_E = 1,
    BLINKY_E,
    PINKY_E,
    CLYDE_E,
    PACMAN_E = PACMAN_REPRESENTATION,
    WALL_E = '#',
    DOT_E = '.',
    PELLET_E = 'O'

} Game_Constructs_t;

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int target_x;
    int target_y;
    int frame_delay;
    int ghost_wait; //when 0 can move, otherwise number of frames until can move
    char over;      //character ghost is over to place back
    Ghost_Mode_t mode;
    Game_Constructs_t ghost_name;
} ghost_t;

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int pacman_wait;
} pacman_t;

typedef struct
{
    char **view;
    int max_x;
    int max_y;
    int pacman_start_offset;
    int pellet_num;
} map_t;

typedef struct
{
    int num_ghosts;
    ghost_t **ghosts;
    pacman_t *pacman;
    int num_frames_ghost_reset; //we wait until 0, then we set ghost to chasing
    int lives;
    int points;
    int high_score;
    map_t *map;
} game_t;

#endif