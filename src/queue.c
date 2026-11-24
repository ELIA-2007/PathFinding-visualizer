#include "queue.h"
#include <stdio.h>

void initQueue(Queue *q) {
    memset(q->nodes, 0, ROWS * COLS);
	q->front = -1;
	q->rear = 0;
}

BOOL isEmpty(Queue *q) {
	return (q->front == q->rear -1) ? TRUE : FALSE;
}

void enqueue(Queue *q, BFSNode nd) {
	q->nodes[q->rear] = nd;
	q->rear++;
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue empty, impossibile to remove!\n");
        return;
    }
    q->front++;
}

BFSNode* peek(Queue *q) {
    if (isEmpty(q)) {
    	printf("Queue empty, impossibile to read!\n");
        return &(BFSNode){67, 67}; //RETURN DEFAULT ERROR VALUE (JUST PRAY THIS DOES NOT FAIL)
    }
    return &q->nodes[q->front + 1];
}