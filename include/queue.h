#pragma once
#include "grid.h"

typedef struct Node{ //BACKWARD LINKED LIST POINTING TO ITS PARENT
	int x;
	int y;
	struct Node *parent;
} Node;

typedef struct { //MOST BASIC "FIFO" QUEUE EVER
	Node nodes[ROWS * COLS];
	int front;
	int rear;
} Queue;


void initQueue(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, Node nd);
void dequeue(Queue *q);
Node* peek(Queue *q);