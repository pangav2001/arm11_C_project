#include "game.h"
#include "priority_queue.h"
#include "dijkstra.h"
#include <stdlib.h>

#define INFINITY 9999
#define NIL -1

void next_step(int starting_x, int starting_y, int target_x, int target_y, int *dx, int *dy, game_t *game)
{
    if (target_x == starting_x && target_y == starting_y)
    {
        *dx = 0;
        *dy = 0;
        return;
    }

    int dist[MAP->max_x][MAP->max_y];
    int prev_x[MAP->max_x][MAP->max_y];
    int prev_y[MAP->max_x][MAP->max_y];

    for (int i = 0; i < MAP->max_x; i++)
    {
        for (int j = 0; j < MAP->max_y; j++)
        {
            dist[i][j] = INFINITY;
            prev_x[i][j] = NIL;
            prev_y[i][j] = NIL;
        }
    }

    dist[starting_x][starting_y] = 0;

    Node_P **pq = new_queue();

    push(pq, starting_x, starting_y, dist[starting_x][starting_y]);

    while (!isEmpty(pq))
    {
        int x;
        int y;
        int distance;
        pop(pq, &x, &y, &distance);

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if ((abs(i) == 1 && abs(j) == 1) || x < 0 || x >= MAP->max_x || y < 0 || y >= MAP->max_y)
                {
                    continue;
                }

                int alt = INFINITY;
                if (get_char(x + i, y + j, MAP) != '#' && get_char(x + i, y + j, MAP) != 'b')
                {
                    alt = dist[x][y] + 1;
                }

                if (alt < dist[x + i][y + j])
                {
                    dist[x + i][y + j] = alt;
                    prev_x[x + i][y + j] = x;
                    prev_y[x + i][y + j] = y;

                    if (!contains(pq, x + i, y + j))
                    {
                        push(pq, x + i, y + j, alt);
                    }
                    else
                    {
                        decrease_priority(pq, x + i, y + j, alt);
                    }
                }
            }
        }
    }

    int x = target_x;
    int y = target_y;

    while (!(prev_x[x][y] == starting_x && prev_y[x][y] == starting_y))
    {
        int temp = prev_x[x][y];
        y = prev_y[x][y];
        x = temp;

        //If position is out of bound return euclidian
        if (x == -1 || y == -1)
        {
            x = target_x;
            y = target_y;
            break;
        }
    }

    //Mod 2 is needed for euclidian case
    *dx = (starting_x - x) % 2;
    *dy = (starting_y - y) % 2;

    //Needed for euclidian in case movement is diagonal
    if (abs(*dx) == 1 && abs(*dy) == 1)
    {
        if (get_char(starting_x + *dx, starting_y, MAP) == '#' || get_char(starting_x + *dx, starting_y, MAP) == 'b')
        {
            *dy = 0;
        }
        else
        {
            *dx = 0;
        }
    }
}