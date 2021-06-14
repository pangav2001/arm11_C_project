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
    int num_ghosts;
    ghost *ghosts;
    pacman pacman;
    int lives;
    int points;
}game;

