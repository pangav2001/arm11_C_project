#include <ncurses.h>
#include "actors.h"
#include "pacman_movement.h"
#include "ghost_movement.h"
#include "game_view.h"
#include <stdlib.h>
#include <string.h>

int game_over(game_t *game);

int main(void) {
    // Setup window
    
    initscr();
    nodelay(stdscr, true);
    cbreak();
    noecho();
    curs_set(FALSE);

    pacman_t *pacman = calloc(1, sizeof(pacman_t));
    game_t *game = calloc(1, sizeof(game_t));
    
    init_game(game, pacman);
    init_map(game);
    
    crate_ghosts(game);
    init_ghosts(game->ghosts, game->num_ghosts, game->map);

    init_pacman(pacman, game->map);
    
  
    int h = 64;
    int w = 64;

    WINDOW* window = newwin(h, w, 0, 0);
    
    while (!game_over(game)) {
        char input = getch();

        int dx = pacman->dx;
        int dy = pacman->dy;

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
        if (check_position_change(pacman, dx, dy, game->map)) {
            pacman->dx = dx;
            pacman->dy = dy;
        }

        move_pacman(pacman, game, game->map);
        move_ghost(game, game->map);

        //update everything else
        update_view(game, game->map);


        //rerender screen
        print_view(window, game);

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