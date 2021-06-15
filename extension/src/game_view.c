#include "game_view.h"
#include "actors.h"
#include <ncurses.h>
#include <unistd.h>

void print_view(WINDOW *window, char **view) {
    clear();
    
    // while (*view != NULL) {
    //     waddstr(window, *view++);
    //     waddstr(window, "\n");
    // }

    for (int i = 0; view[i]; i++) {
        mvprintw(i, 0, view[i]);
    }

    wrefresh(window);
    usleep(50000);
    
}

void set_character(int x, int y, char c, char **view) {
    view[y][x] = c;
}

char get_char(int x, int y, char **view) {
    return view[y][x];
}

void update_view(game_t *game, char **view) {
    //update pacman
    set_character(game->pacman->x, game->pacman->y, game->pacman->representation, view);
    

    //update ghosts

    //
}
