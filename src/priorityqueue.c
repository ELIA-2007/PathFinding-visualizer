#include "priorityqueue.h"
#include <stdio.h>
#include <string.h>

void PQinitQueue(PrioQueue *pq) {
	memset(pq->nodes, 0, sizeof(pq->nodes));
	pq->size = 0;
	pq->index = 0;
}

BOOL PQisEmpty(PrioQueue *pq) {
	return (!pq->size) ? TRUE : FALSE;
}

void swap(AstarNode *nd1, AstarNode *nd2) {
	AstarNode temp = *nd1;
	*nd1 = *nd2;
	*nd2 = temp;
}
void heapifyUp(PrioQueue* pq, int index) {
    if (index && pq->nodes[(index - 1) / 2].f > pq->nodes[index].f) {
        swap(&pq->nodes[(index - 1) / 2], &pq->nodes[index]);
        heapifyUp(pq, (index - 1) / 2);
    }
}

void heapifyDown(PrioQueue* pq, int index) {
	int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->nodes[left].f < pq->nodes[smallest].f)
        smallest = left;

    if (right < pq->size && pq->nodes[right].f < pq->nodes[smallest].f)
        smallest = right;

    if (smallest != index) {
        swap(&pq->nodes[index], &pq->nodes[smallest]);
        heapifyDown(pq, smallest);
    }
}

void PQenqueue(PrioQueue *pq, AstarNode nd) {
	if (pq->size == ROWS * COLS) {
        printf("Priority queue is full\n");
        return;
    }

    pq->nodes[pq->size++] = nd;
    heapifyUp(pq, pq->size - 1);
}
AstarNode PQdequeue(PrioQueue *pq) {
	if (!pq->size) {
		printf("Priority queue is empty\n");
		return (AstarNode){67, 67, 67}; //JUST HOPE THIS NEVER FAILS
	}
	AstarNode node = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    heapifyDown(pq, 0);
    return node;

}
AstarNode PQpeek(PrioQueue *pq) {
	if (!pq->size) {
        printf("Priority queue is empty\n");
        return (AstarNode){67, 67, 67}; //JUST HOPE THIS NEVER FAILS
    }
    return pq->nodes[0];
}