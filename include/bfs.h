#pragma once
#include "queue.h"

typedef struct { //STRUCT TO KEEP PROGRESS FROM ONE STEP TO ANOTHER
	int finished;
	Queue q;
} BFSState;

void initBFS(BFSState *state, grid grd, int startX, int startY);
int bfs(grid grd, BFSState *state);