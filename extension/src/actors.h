#ifndef ACTORS_H
#define ACTORS_H

#define MAX_GHOSTS 9
#define GHOST_WAIT 1
#define PACMAN_WAIT 1
#define GHOST_START_DELAY 20 //between ghosts starting
#define GHOST game->ghosts

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
    int pacman_wait;
    char representation;
} pacman_t;

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int target_x;
    int target_y;
    char representation;
    int ghost_wait; //when 0 can move, otherwise number of frames until can move
    char over; //character ghost is over to place back
    Ghost_Mode_t mode;
} ghost_t;
typedef struct
{
    char**view;
    int max_x;
    int max_y;
    int pacman_start_offset;   
}map_t;

typedef struct
{
    int num_ghosts;
    ghost_t **ghosts;
    pacman_t *pacman;
    int num_frames_ghost_reset; //-1 means ignore, we wait until 0, then we set ghost to chasing
    int lives;
    int points;
    int high_score;
    map_t *map;
} game_t;


void init_game(game_t *game, pacman_t *pacman);

void init_pacman(pacman_t *pacman, map_t *map);

void kill_pacman(pacman_t *pacman, game_t *game, char **view);

void crate_ghosts(game_t *game);

void free_ghosts(game_t *game);

void init_ghosts(ghost_t **ghosts, int num_ghosts, map_t *map);

void kill_ghost(ghost_t *ghost, char **view);

void revive_ghost(ghost_t *ghost, char **view);

void init_map(game_t *game);

#endif