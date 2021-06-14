#include "game_view.h"

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
