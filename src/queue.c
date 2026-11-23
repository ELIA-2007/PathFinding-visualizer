#include "queue.h"
#include <stdio.h>

void initQueue(queue *q) {
	q->front = -1;
	q->rear = 0;
}

int isEmpty(queue *q) {
	return (q->front == q->rear -1) ? 1 : 0;
}

void enqueue(queue *q, node _node) {
	q->nodes[q->rear] = _node;
	q->rear++;
}

void dequeue(queue *q) {
    if (isEmpty(q)) {
        printf("Coda vuota, impossibile rimuovere\n");
        return;
    }
    q->front++;
}

node* peek(queue *q) {
    if (isEmpty(q)) {
    	printf("Coda vuota, impossibile leggere\n");
        return &(node){67, 67};
    }
    return &q->nodes[q->front + 1];
}