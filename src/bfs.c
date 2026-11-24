#include "bfs.h"
#include <stdio.h>
//INIT STATE STRUCT AND GET STARTING CELLS
void initBFS(BFS_State *state, grid grd, int startX, int startY) {
    initQueue(&state->q);
    Node start = (Node){startX, startY, NULL};
    enqueue(&state->q, start);
    state->finished = 0;
    for (int x = 0; x < COLS; x++) //RESETTING VISITED CELLS (I KNOW I SHOULD BE DOING THIS IN A GRID FUNCTION)
    	for (int y = 0; y < ROWS; y++)
    		if (grd[x][y] == visited || grd[x][y] == path)
    		grd[x][y] = empty;
}

int bfs(grid grd, BFS_State *state) { //STEPS (RETURN 0 IF FINISHED, 1 IF NOT)
	if (isEmpty(&state->q) || state->finished == 1) return 0;

	//POSSILE MOVES (RIGHT LEFT UP DOWN)
	int moveRow[] = {-1, 1, 0, 0};
	int moveCol[] = {0, 0, -1, 1};

	//GET FIRST QUEUE NODE AND KICK THE LAST
	Node *current = peek(&state->q);
	Node next;
    dequeue(&state->q);

	for (int i=0;i<4;i++) {
		next.x = current->x + moveRow[i];
		next.y = current->y + moveCol[i];
		next.parent = current; //SET PARENT OF THE NEXT CELL TO A POINTER TO THE CURRENT CELL
		if (next.x >= 0 && next.x < COLS && next.y >= 0 && next.y < ROWS) {
			Cell *nextCell = &grd[next.x][next.y];

			if (*nextCell == empty) { //IF ITS EMPTY ENQUEUE THAT AND MARK THAT AS VISITED
				*nextCell = visited;
				enqueue(&state->q, next);
			}
			else if (*nextCell == end) { //IF ITS THE TARGET RETURN 0
				state->finished = 1;
			}
		}
	}

	if (state->finished == 1) { //IF PATH IS FOUND SET PATH CELLS TO "PATH"
		while (grd[current->x][current->y] != start) {
    		grd[current->x][current->y] = path;
    		current = current->parent;
		}
		return 0;
	}
	else 
		return 1;
}