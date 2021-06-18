#include "headers/priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Node_P **new_queue()
{
    Node_P **ret = malloc(sizeof(Node_P *));
    assert(ret);

    return ret;
}

static Node_P *new_node(int x, int y, int distance)
{
    Node_P *node = (Node_P *)malloc(sizeof(Node_P));
    assert(node);

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

int contains(Node_P **head, int x, int y)
{
    Node_P *start = *head;

    while (start)
    {
        if (start->x == x && start->y == y)
        {
            return 1;
        }

        start = start->next;
    }

    return 0;
}

static void delete_node(Node_P **head, int x, int y)
{
    Node_P *prev;
    Node_P *curr = *head;

    while (prev && curr && !(curr->x == x && curr->y == y))
    {
        prev = curr;
        curr = curr->next;
    }

    assert(prev);
    assert(curr);

    prev->next = curr->next;

    free(curr);
}

void decrease_priority(Node_P **head, int x, int y, int distance)
{
    delete_node(head, x, y);

    push(head, x, y, distance);
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