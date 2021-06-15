#include "game_view.h"
#include "actors.h"

void print_view(WINDOW *window, char **view) {
    refresh();
    while (*view != NULL) {
        waddstr(window, *view++);
        waddstr(window, "\n");
    }
    wrefresh(window);
}

void set_character(int x, int y, char c, char **view) {
    view[x][y] = c;
}

char get_char(int x, int y, char **view) {
    return view[x][y];
}

void update_view(game_t *game, char **view) {
    //update pacman
    set_character(game->pacman->x, game->pacman->y, game->pacman->representation, view);
    

    //update ghosts

    //
}
