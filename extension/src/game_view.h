#include <stdio.h>
#include "curses.h"

char *view[] = {
"#######################################",
"# . . . . . . . . ### . . . . . . . . #",
"# O ### . ##### . ### . ##### . ### O #",
"# . . . . . . . . . . . . . . . . . . #",
"# . ### . # . ########### . # . ### . #",
"# . . . . # . . . ### . . . # . . . . #",
"####### . ##### . ### . ##### . #######",
"      # . # . . . . . . . . # . #      ",
"      # . # . ### - - ### . # . #      ",
"####### . # . #         # . # . #######",
"        . . . #         # . . .        ",
"####### . # . #         # . # . #######",
"      # . # . ########### . # . #      ",
"      # . # . . . . . . . . # . #      ",
"####### . # . ########### . # . #######",
"# . . . . . . . . ### . . . . . . . . #",
"# O ### . ##### . ### . ##### . ### O #",
"# . . # . . . . . . . . . . . . # . . #",
"### . # . # . ########### . # . # . ###",
"# . . . . # . . . ### . . . # . . . . #",
"# . ########### . ### . ########### . #",
"# . . . . . . . . . . . . . . . . . . #",
"#######################################",                        
    NULL
};

void print_view(WINDOW *window, char **view);

