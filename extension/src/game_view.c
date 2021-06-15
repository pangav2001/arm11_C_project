#include "game_view.h"
#include "actors.h"
#include <ncurses.h>
#include <unistd.h>

#define UI_HEIGHT 2

void print_view(WINDOW *window, char **view, game_t *game) {
    clear();
    
    // while (*view != NULL) {
    //     waddstr(window, *view++);
    //     waddstr(window, "\n");
    // }
    mvprintw(0, 1, "1UP\t\t HIGH SCORE");
    mvprintw(1, 1, "  %d\t\t%9d", game->points, game->high_score);

    int i = 0;
    for (; view[i]; i++) {
        mvprintw(i + UI_HEIGHT, 1, view[i]);
    }

    i++;

    for(int j = 0; j < game->lives - 1; j++)
    {
        mvprintw(i + UI_HEIGHT, j * 2, "%c", game->pacman->representation);
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
