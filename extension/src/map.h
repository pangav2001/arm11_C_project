#ifndef MAP_H
#define MAP_H

typedef struct
{
    char**view;
    int max_x;
    int max_y;
    int pacman_start_offset;   
}map_t;

void print_view(char **view);

void set_char(int x, int y, char ch, map_t *map);

char get_char(int x, int y, map_t *map);

#endif
