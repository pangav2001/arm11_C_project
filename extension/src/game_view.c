#include "game_view.h"
#include "actors.h"
#include <ncurses.h>
#include <unistd.h>

#define UI_HEIGHT 2

void print_view(WINDOW *window, game_t *game) {
    clear();
    
    // while (*view != NULL) {
    //     waddstr(window, *view++);
    //     waddstr(window, "\n");
    // }
    mvprintw(0, 1, "1UP\t\t HIGH SCORE");
    mvprintw(1, 1, "  %d\t\t%9d", game->points, game->high_score);

    int i = 0;
    for (; game->map->view[i]; i++) {
        mvprintw(i + UI_HEIGHT, 1, game->map->view[i]);
    }

    i++;

    for(int j = 0; j < game->lives - 1; j++)
    {
        mvprintw(i + UI_HEIGHT, j * 2, "%c", game->pacman->representation);
    }

    wrefresh(window);
    usleep(50000);
    
}

void set_character(int x, int y, char c, map_t *map) {
    map->view[y][x] = c;
}

char get_char(int x, int y, map_t *map) {
    return map->view[y][x];
}

void update_view(game_t *game, map_t *map) {
    //update pacman
    set_character(game->pacman->x, game->pacman->y, game->pacman->representation, map);
    

    //update ghosts

    //
}
