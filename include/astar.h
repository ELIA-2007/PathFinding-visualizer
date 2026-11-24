#pragma once
#include "priorityqueue.h"
#include "grid.h"

typedef struct {
	BOOL finished;
	PrioQueue pq;
} AstarState;

void initAstar(AstarState *state, grid grd, int startX, int startY);
BOOL aStar(grid grd, AstarState *state, int endX, int endY);