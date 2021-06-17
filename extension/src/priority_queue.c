#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Node_P **new_queue()
{
    return malloc(sizeof(Node_P *));
}

static Node_P *new_node(int x, int y, int distance)
{
    Node_P *node = (Node_P *)malloc(sizeof(Node_P));

    node->x = x;
    node->y = y;
    node->distance = distance;
    node->next = NULL;

    return node;
}

void pop(Node_P **head, int *x, int *y, int *distance)
{
    assert(!isEmpty(head));

    Node_P *temp = *head;
    *head = temp->next;

    *x = temp->x;
    *y = temp->y;
    *distance = temp->distance;

    free(temp);
}

int isEmpty(Node_P **head)
{
    return *head == NULL;
}

void push(Node_P **head, int x, int y, int distance)
{
    if (isEmpty(head))
    {
        *head = new_node(x, y, distance);
    }
    else
    {
        Node_P *curr = *head;
        Node_P *to_insert = new_node(x, y, distance);

        if ((*head)->distance > distance)
        {
            to_insert->next = *head;
            *head = to_insert;
        }
        else
        {
            while (curr->next != NULL &&
                   curr->next->distance < distance)
            {
                curr = curr->next;
            }

            to_insert->next = curr->next;
            curr->next = to_insert;
        }
    }
}

void free_queue(Node_P **head)
{
    while (!isEmpty(head))
    {
        int x;
        int y;
        int distance;
        pop(head, &x, &y, &distance);
    }

    free(head);
}