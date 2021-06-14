#include "game_view.h"
#include "actors.h"

void print_view(WINDOW *window, char **view) {
    while (*view != NULL) {
        waddstr(window, *view++);
        waddstr(window, "\n");
    }
    wrefresh(window);
}

void set_character(int x, int y, char c) {
    view[x][y] = c;
}

char get_char(int x, int y) {
    return view[x][y];
}

void update_view(game_t *game) {
    //update pacman
    set_character(game->pacman->x, game->pacman->y, game->pacman->representation);
    

    //update ghosts

    //
}
