#include "astar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initAstar(AstarState *state, grid grd, int startX, int startY) {
	PQinitQueue(&state->pq);
	AstarNode firstNode = (AstarNode){startX, startY, 0.00f, 0.00f};
	PQenqueue(&state->pq, firstNode);
	resetVisited(grd);
	for (int x=0;x<COLS;x++) {
		for (int y=0;y<ROWS;y++) {
			state->g[x][y] = INFINITY;
		}
	}
	state->g[startX][startY] = 0.00f;
	state->finished = FALSE;
}

BOOL aStar(grid grd, AstarState *state, int endX, int endY) {
	if (PQisEmpty(&state->pq) || state->finished) return FALSE;
	int moveX[] = {1, -1, 0, 0, 1, -1, 1, -1};
	int moveY[] = {0, 0, 1, -1, 1, -1, -1, 1};

	AstarNode current = PQdequeue(&state->pq);
	AstarNode next;
	float nextG, nextH;

	if (grd[current.x][current.y] == end) {
		Coord cell = state->parents[current.x][current.y];
		while (grd[cell.x][cell.y] != start) {
			grd[cell.x][cell.y] = path;
			cell = state->parents[cell.x][cell.y];
		}
		state->finished = TRUE;
		return FALSE;
	}

	for (int i=0;i<8;i++) {
		next.x = current.x + moveX[i];
		next.y = current.y + moveY[i];
		if (!isMoveValid(grd, next.x, next.y, i)) continue;
		nextG = state->g[current.x][current.y] + ((i < 4) ? 1.f : sqrtf(2.f));
		if (nextG < state->g[next.x][next.y]) {//IF BETTER PATH TO THIS CELL IS FOUND
			nextH = sqrt((float)pow(abs(next.x - endX), 2) + (float)pow(abs(next.y - endY), 2));
			next.f = nextH + next.g;
			if (state->g[next.x][next.y] == INFINITY) { //IF FIRST TIME CHECKING IT, ENQUEUE
				if (grd[next.x][next.y] == empty)
					grd[next.x][next.y] = visited;
				PQenqueue(&state->pq, next);
			} else { //IF IT WAS ALREADY IN THE QUEUE BUT WITH A LESS EFFICIENT PATH, REPLACE IT
				for (int k = 0; k < state->pq.size; k++) {
					if (state->pq.nodes[k].x == next.x && state->pq.nodes[k].y == next.y) {
						state->pq.nodes[k] = next;
						heapifyUp(&state->pq, k);
						break;
					}
				}
			}
			state->g[next.x][next.y] = nextG;
			state->parents[next.x][next.y] = (Coord){current.x, current.y};
		}
	}
	
	return (!state->finished);
}