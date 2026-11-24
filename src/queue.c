#include "queue.h"
#include <stdio.h>

void initQueue(Queue *q) {
	q->front = -1;
	q->rear = 0;
}

int isEmpty(Queue *q) {
	return (q->front == q->rear -1) ? 1 : 0;
}

void enqueue(Queue *q, Node nd) {
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

Node* peek(Queue *q) {
    if (isEmpty(q)) {
    	printf("Queue empty, impossibile to read!\n");
        return &(Node){67, 67}; //RETURN DEFAULT ERROR VALUE (JUST PRAY THIS DOES NOT FAIL)
    }
    return &q->nodes[q->front + 1];
}