#include "curses.h"

int main(void) {
    // Setup window

    initscr();
    nodelay(stdscr, true);
    cbreak();
    
    int h = 64;
    int w = 64;

    WINDOW* window = newwin(h, w, 0, 0);
    
    while (!game_over()) {
        char input = getch();

        switch (input) {
            case 'w':
                
                break;
            case 'a':

                break;
            case 's':

                break;
            case 'd':

                break;
            default:
                // do nothing
        }


    }
        
    //
    endwin();
}

int game_over(void) {
    return 0;
}