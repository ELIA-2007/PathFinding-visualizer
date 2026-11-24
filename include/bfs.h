#pragma once
#include "queue.h"

typedef struct {
	int finished;
	Queue q;
} BFS_State;

void initBFS(BFS_State *state, grid grd, int startX, int startY);
int bfs(grid grd, BFS_State *state);