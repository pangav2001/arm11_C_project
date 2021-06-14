typedef enum Ghost_Mode {
    CHASING,
    CHASED,
    EATEN,
    OFF
}Ghost_Mode;


typedef struct pacman{
    int x;
    int y;
    int dx;
    int dy;
    char representation;
}pacman;


typedef struct ghost{
    int x;
    int y;
    int dx;
    int dy;
    char representation;
    Ghost_Mode mode;
}ghost;

typedef struct game {
    ghost *ghosts;
    pacman pacman;
    int num_frames_ghost_reset; //-1 means ignore, we wait until 0, then we set ghost to chasing
    int lives;
    int points;
}game;

