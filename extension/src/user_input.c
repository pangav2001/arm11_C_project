#include <stdio.h>
#include "curses.h"
#include "user_input.h"

Movement get_position() {
    return getch();
}

// int main(void) {
//     printf("Welcome to test input\n");
    
//     ///
//     initscr();
//     nodelay(stdscr, true);
//     cbreak();

//     for (int i = 0; i < 10; i++) {
//         sleep(1);
//         int ch;
//         ch = getch();
    
//         ////
//         printf("input was: %d\n", ch);
//     }

    
//     endwin();
//     printf("Done test\n");
// }