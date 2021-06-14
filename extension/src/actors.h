#define MAX_GHOSTS 9

typedef enum {
    CHASING,
    SCATTER,
    FRIGHTENED,
    EATEN,
    OFF
}Ghost_Mode_t;


typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    char representation;
}pacman_t;


typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int target_x;
    int target_y;
    char representation;
    char over;
    Ghost_Mode_t mode;
}ghost_t;

typedef struct {
    int num_ghosts;
    ghost_t **ghosts;
    pacman_t pacman;
    int num_frames_ghost_reset; //-1 means ignore, we wait until 0, then we set ghost to chasing
    int lives;
    int points;
}game_t;

void init_game(game_t *game);

void init_pacman(pacman_t *pacman);

void kill_pacman(pacman_t *pacman, game_t *game);

void crate_ghosts(game_t *game);

void free_ghosts(game_t *game);

void init_ghosts(ghost_t **ghosts, int num_ghosts);

void kill_ghost(ghost_t *ghost);

void revive_ghost(ghost_t *ghost);