typedef enum {
    CHASING,
    CHASED,
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
    char representation;
    Ghost_Mode_t mode;
}ghost_t;

typedef struct {
    int num_ghosts;
    ghost_t *ghosts;
    pacman_t pacman;
    int num_frames_ghost_reset; //-1 means ignore, we wait until 0, then we set ghost to chasing
    int lives;
    int points;
}game_t;

