#include "curses.h"

int main(void) {
    // Setup window

    initscr();
    nodelay(stdscr, true);
    cbreak();
    
    int h = 64;
    int w = 64;

    WINDOW* window = newwin(h, w, 0, 0);
    
    
    
    
    
    
    
    
    
    
    
    
    //
    endwin();
}