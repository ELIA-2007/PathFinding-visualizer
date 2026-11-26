#include "bfs.h"
#include <stdio.h>
//INIT STATE STRUCT AND GET STARTING CELLS
void initBFS(BFSState *state, grid grd, int startX, int startY) {
	resetVisited(grd);
    initQueue(&state->q);
    state->finished = FALSE;
    BFSNode firstNode = (BFSNode){startX, startY, NULL};
    enqueue(&state->q, firstNode);
}

BOOL bfs(grid grd, BFSState *state, int *steps) { //STEPS (RETURN 0 IF FINISHED, 1 IF NOT)
	if (isEmpty(&state->q) || state->finished) return FALSE;

	//POSSILE MOVES (RIGHT LEFT UP DOWN)
	int moveX[] = {-1, 1, 0, 0};
	int moveY[] = {0, 0, -1, 1};

	//GET FIRST QUEUE NODE AND KICK THE LAST
	BFSNode *current = peek(&state->q);
	BFSNode next;
    dequeue(&state->q);

	for (int i=0;i<4;i++) {
		next.x = current->x + moveX[i];
		next.y = current->y + moveY[i];
		next.parent = current; //SET PARENT OF THE NEXT CELL TO A POINTER TO THE CURRENT CELL
		if (!isMoveValid(grd, next.x, next.y, i)) continue;
		Cell *nextCell = &grd[next.x][next.y];

		if (*nextCell == empty) { //IF ITS EMPTY ENQUEUE THAT AND MARK THAT AS VISITED
			(*steps)++;
			*nextCell = visited;
			enqueue(&state->q, next);
		}
		else if (*nextCell == end) { //IF ITS THE TARGET SET FINISHED TO TRUE
			state->finished = TRUE;
		}
	}

	if (state->finished) { //IF PATH IS FOUND SET PATH CELLS TO "PATH"
		while (grd[current->x][current->y] != start) {
    		grd[current->x][current->y] = path;
    		current = current->parent;
		}
	}
	return (!state->finished);
}