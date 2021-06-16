#include "game.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DELAY 50000

game_t *create_game()
{
    game_t *ret = (game_t *)malloc(sizeof(game_t));

    create_pacman(ret);
    create_map(ret);

    return ret;
}

void free_game(game_t *game)
{
    free_pacman(game);
    free_ghosts(game);
    free_map(game);

    free(game);
}

void init_game(game_t *game)
{
    game->lives = 3;
    game->num_frames_ghost_reset = -1;

    game->num_ghosts = 4;
    game->points = 0;
    game->high_score = 10700;

    init_map(game);
    init_pacman(game);
    create_ghosts(game);
    init_all_ghosts(game);
}

void print_game_over()
{
    int max_y;
    int max_x;
    getmaxyx(stdscr, max_y, max_x);

    for (int i = max_x; i >= 0; i--)
    {
        clear();

        int len = strlen(" _____   ___  ___  ___ _____   _____  _   _ ___________ ") / 2;

        //Change 'G'
        mvprintw(max_y / 2, i, "%c  %c %c %c %c", PACMAN_REPRESENTATION, 'G', 'G', 'G', 'G');
        mvprintw(max_y / 2 + 1, max_x / 2 - len, " _____   ___  ___  ___ _____   _____  _   _ ___________ ");
        mvprintw(max_y / 2 + 2, max_x / 2 - len, "|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | |  ___| ___ \\");
        mvprintw(max_y / 2 + 3, max_x / 2 - len, "| |  \\// /_\\ \\| .  . || |__   | | | || | | | |__ | |_/ /");
        mvprintw(max_y / 2 + 4, max_x / 2 - len, "| | __ |  _  || |\\/| ||  __|  | | | || | | |  __||    / ");
        mvprintw(max_y / 2 + 5, max_x / 2 - len, "| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ / |___| |\\ \\ ");
        mvprintw(max_y / 2 + 6, max_x / 2 - len, " \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/\\____/\\_| \\_|");

        refresh();

        usleep(DELAY);
    }
}

int main(void)
{
    // Setup window

    initscr();
    nodelay(stdscr, true);
    cbreak();
    noecho();
    curs_set(FALSE);

    game_t *game = create_game();

    init_game(game);

    int h = 64;
    int w = 64;

    WINDOW *window = newwin(h, w, 0, 0);

    while (!game_over(game))
    {
        char input = getch();

        int dx = PACMAN->dx;
        int dy = PACMAN->dy;

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

        move_ghosts(game);
        for (int i = 0; i < game->num_ghosts; i++)
        {
            if (GHOSTS[i]->x == PACMAN->x && GHOSTS[i]->y == PACMAN->y)
                switch (GHOSTS[i]->mode)
                {
                case SCATTER:
                case CHASING:
                    kill_pacman(game);
                    continue;
                    break;
                case FRIGHTENED:
                    //TODO
                    break;
                default:
                    break;
                }
        }

        move_pacman(game, dx, dy);

        if (MAP->pellet_num <= 0)
        {
            init_all_ghosts(game);
            init_pacman(game);
            init_map(game);
        }

        //update everything else
        //update_view(game);

        //rerender screen
        print_view(window, game);
    }

    print_game_over();

    endwin();

    free_game(game);
}

int game_over(game_t *game)
{
    return game->lives <= 0;
}
