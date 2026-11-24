#pragma once
#include "queue.h"

typedef struct { //STRUCT TO KEEP PROGRESS FROM ONE STEP TO ANOTHER
	BOOL finished;
	Queue q;
} BFSState;

void initBFS(BFSState *state, grid grd, int startX, int startY);
BOOL bfs(grid grd, BFSState *state);