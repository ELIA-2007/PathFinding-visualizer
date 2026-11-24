#pragma once
#include "grid.h"

typedef struct BFSNode{ //BACKWARD LINKED LIST POINTING TO ITS PARENT
	int x, y;
	struct BFSNode *parent;
} BFSNode;

typedef struct { //MOST BASIC "FIFO" QUEUE EVER
	BFSNode nodes[ROWS * COLS];
	int front, rear;
} Queue;

void initQueue(Queue *q);
BOOL isEmpty(Queue *q);
void enqueue(Queue *q, BFSNode nd);
void dequeue(Queue *q);
BFSNode* peek(Queue *q);