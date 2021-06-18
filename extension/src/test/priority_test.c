#include "testutils.h"
#include "../priority_queue.h"

int main(void) {
    Node_P **PQ = new_queue();

    testcond(isEmpty(PQ), "Empty PQ");

    push(PQ, 0, 1, 10);
    push(PQ, 2, 4, 5);

    int x;
    int y;
    int dist;

    testcond(contains(PQ,0,1) && contains(PQ,2,4), "Contains when item is inserted");
    testcond(!contains(PQ,2,1) && !contains(PQ,0,4), "Contains works when not inserted");
    testcond(!isEmpty(PQ), "Not Empty PQ");
    pop(PQ, &x, &y, &dist);
    testcond(x ==2 && y == 4 && dist == 5, "Pop correct order");
    testcond(!isEmpty(PQ), "Not Empty PQ");
    pop(PQ, &x, &y, &dist);
    testcond(x ==0 && y == 1 && dist == 10, "Pop correct order 2");
    testcond(isEmpty(PQ), "Empty PQ");

    free_queue(PQ);
}

