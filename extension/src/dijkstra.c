#include "game.h"
#include "priority_queue.h"
#include <stdlib.h>

#define INFINITY 9999
#define NIL -1

int main()
{
    int starting_x = 21;
    int starting_y = 7;

    int target_x = 12;
    int target_y = 10;

    if (target_x == starting_x && target_y == starting_y)
    {
        return 0;
    }

    game_t *game = (game_t *)malloc(sizeof(game_t));

    create_map(game);

    init_map(game);

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

    push(pq, starting_x, starting_y, 0);

    while (!isEmpty(pq))
    {
        int x;
        int y;
        int distance;
        pop(pq, &x, &y, &distance);
        if (y == target_y && x == target_x)
        {
            break;
        }

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (abs(i) == 1 && abs(j) == 1)
                {
                    continue;
                }

                if (x + i >= 0 &&  x + i < MAP->max_x && y + j >= 0 && y + j < MAP->max_y && get_char(x + i, y + j, MAP) != '#' && dist[x + i][y + j] > dist[x][y] + 1)
                {
                    dist[x + i][y + j] = dist[x][y] + 1;
                    prev_x[x + i][y + j] = x;
                    prev_y[x + i][y + j] = y;

                    push(pq, x + i, y + i, dist[x + i][y + j]);
                }
            }
        }
    }

    int x = target_x;
    int y = target_y;

    while (prev_x[x][y] != starting_x && prev_y[x][y] != starting_y)
    {
        int temp = prev_x[x][y];
        y = prev_y[x][y];
        x = temp;
    }
    return 0;
    
}