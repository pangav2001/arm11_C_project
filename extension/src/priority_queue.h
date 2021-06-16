#ifndef _PRRIORITY_H_
#define _PRRIORITY_H_

typedef struct node
{
    int x;
    int y;
    int distance;
    struct node *next;
} Node_P;

void pop(Node_P **head, int *x, int *y, int *distance);

void push(Node_P **head, int x, int y, int distance);

int contains(Node_P **head, int x, int y);

int isEmpty();

#endif