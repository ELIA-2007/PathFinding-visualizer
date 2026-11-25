#pragma once
#include "settings.h"

typedef struct {
	int x, y;
	float g, f;
} AstarNode;

typedef struct {
	AstarNode nodes[ROWS * COLS];
	int size, index;
} PrioQueue;

void PQinitQueue(PrioQueue *pq);
BOOL PQisEmpty(PrioQueue *pq);
void swap(AstarNode *nd1, AstarNode *nd2);
void heapifyUp(PrioQueue* pq, int index);
void heapifyDown(PrioQueue* pq, int index);
void PQenqueue(PrioQueue *pq, AstarNode nd);
AstarNode PQdequeue(PrioQueue *pq);
AstarNode PQpeek(PrioQueue *pq);