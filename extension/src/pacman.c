#include "curses.h"
#include "actors.h"
#include "pacman_movement.h"
#include "game_view.h"

int main(void) {
    // Setup window

    initscr();
    nodelay(stdscr, true);
    cbreak();

    pacman_t *pacman = calloc(1, sizeof(pacman_t));
    game_t *game = calloc(1, sizeof(game_t));

    init_pacman(pacman);
    init_game(game, pacman);
  
    int h = 64;
    int w = 64;

    WINDOW* window = newwin(h, w, 0, 0);
    
    while (!game_over(game)) {
        char input = getch();

        int dx;
        int dy;

        switch (input) {
            case 'w':
                dy = -1;
                dx = 0;

                break;
            case 'a':
                dy = 0;
                dx = -1;
                break;
            case 's':
                dy = 1;
                dx = 0;

                break;
            case 'd':
                dy = 0;
                dx = 1;
                break;
        }
        //make movement
        if (check_position_change(pacman, dx, dy)) {
            pacman->dx = dx;
            pacman->dy = dy;
        }

        move_pacman(pacman, game);

        //update everything else
        update_view(game);


        //rerender screen
        print_view(window, view);

    }
        
    //
    endwin();

    //
    free(game);
    free(pacman);
}

int game_over(game_t *game) {
    return game->lives <= 0;
}