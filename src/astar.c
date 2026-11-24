#include "astar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initAstar(AstarState *state, grid grd, int startX, int startY) {
	PQinitQueue(&state->pq);
	AstarNode firstNode = (AstarNode){startX, startY, 0.00f, 0.00f, NULL};
	PQenqueue(&state->pq, firstNode);
	resetVisited(grd);
	state->finished = FALSE;
}

BOOL aStar(grid grd, AstarState *state, int endX, int endY) {
	if (PQisEmpty(&state->pq) || state->finished) return FALSE;
	int moveX[] = {1, -1, 0, 0, 1, -1, 1, -1};
	int moveY[] = {0, 0, 1, -1, 1, -1, -1, 1};

	AstarNode *current = PQdequeue(&state->pq);
	AstarNode next;
	float g, h;

	for (int i=0;i<8;i++) {
		next.x = current->x + moveX[i];
		next.y = current->y + moveY[i];
		next.parent = current;
		if (next.x >= 0 && next.x < COLS && next.y >= 0 && next.y < ROWS) { //IF NEXT CELL IS INSIDE THE GRID
			Cell *nextCell = &grd[next.x][next.y];
			if (*nextCell == end) {//IF ITS THE TARGET SET FINISHED TO TRUE
				state->finished = TRUE;
				break;
			}
			else {
				h = sqrt(pow(abs(next.x - endX), 2) + pow(abs(next.y - endY), 2));//PITAGORA DISTANCE APPROXIMATION
				next.g = ((i<4) ? 1.f : sqrt(2)) + current->g; //1 IF ITS DIRECTLY NEXT TO PARENT, SQRT(2) IF ITS DIAGONALLY NEXT TO IT
				next.f = next.g + h;
				if (*nextCell == empty) {
					*nextCell = visited;
					PQenqueue(&state->pq, next);
				}
			}
		}
	}
	
	return (!state->finished);
}