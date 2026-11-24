#pragma once
#include "grid.h"

typedef struct Node{
	int x;
	int y;
	struct Node *parent;
} Node;

typedef struct {
	Node nodes[ROWS * COLS];
	int front;
	int rear;
} Queue;


void initQueue(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, Node nd);
void dequeue(Queue *q);
Node* peek(Queue *q);