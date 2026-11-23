#include "grid.h"

typedef struct node{
	int x;
	int y;
	struct node *parent;
} node;

typedef struct {
	node nodes[ROWS * COLS];
	int front;
	int rear;
} queue;


void initQueue(queue *q);
int isEmpty(queue *q);
void enqueue(queue *q, node _node);
void dequeue(queue *q);
node* peek(queue *q);