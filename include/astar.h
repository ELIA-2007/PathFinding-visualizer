#pragma once
#define INFINITY 100000
#include "priorityqueue.h"
#include "grid.h"

typedef struct {
	int x, y;
} Coord;

typedef struct {
	BOOL finished;
	PrioQueue pq;
	float g[COLS][ROWS];
	Coord parents[COLS][ROWS];

} AstarState;

void initAstar(AstarState *state, grid grd, int startX, int startY);
BOOL aStar(grid grd, AstarState *state, int endX, int endY);