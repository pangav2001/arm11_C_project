#include <ncurses.h>
#include "actors.h"
#include "pacman_movement.h"
#include "ghost_movement.h"
#include "game_view.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int game_over(game_t *game);

int main(void)
{
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

    WINDOW *window = newwin(h, w, 0, 0);

    while (!game_over(game))
    {
        char input = getch();

        int dx = pacman->dx;
        int dy = pacman->dy;

        switch (input)
        {
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
        flushinp();

        move_ghost(game, game->map);
        if (!check_pacman_collision(game))
        {
            move_pacman(pacman, game, game->map, dx, dy);
        }
        update_ghost_targets(game, game->map);

        //update everything else
        update_view(game, game->map);

        //rerender screen
        print_view(window, game);
    }

    int max_y;
    int max_x;
    getmaxyx(stdscr, max_y, max_x);

    for (int i = max_x; i >= 0; i--)
    {
        clear();

        int len = strlen(" _____   ___  ___  ___ _____   _____  _   _ ___________ ") / 2;

        mvprintw(max_y / 2, i, "%c  %c %c %c %c", game->pacman->representation, game->ghosts[0]->representation, game->ghosts[0]->representation, game->ghosts[0]->representation, game->ghosts[0]->representation);
        mvprintw(max_y / 2 + 1, max_x / 2 - len, " _____   ___  ___  ___ _____   _____  _   _ ___________ ");
        mvprintw(max_y / 2 + 2, max_x / 2 - len, "|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | |  ___| ___ \\");
        mvprintw(max_y / 2 + 3, max_x / 2 - len, "| |  \\// /_\\ \\| .  . || |__   | | | || | | | |__ | |_/ /");
        mvprintw(max_y / 2 + 4, max_x / 2 - len, "| | __ |  _  || |\\/| ||  __|  | | | || | | |  __||    / ");
        mvprintw(max_y / 2 + 5, max_x / 2 - len, "| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ / |___| |\\ \\ ");
        mvprintw(max_y / 2 + 6, max_x / 2 - len, " \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/\\____/\\_| \\_|");

        refresh();

        usleep(50000);
    }

    //
    endwin();

    //
    free(game);
    free(pacman);
}

int game_over(game_t *game)
{
    return game->lives <= 0;
}