#include "bfs.h"
#include <stdio.h>

void initBFS(BFS_State *state, grid grd, int startX, int startY) {
    initQueue(&state->q);
    Node start = (Node){startX, startY, NULL};
    enqueue(&state->q, start);
    state->finished = 0;
    for (int x = 0; x < COLS; x++)
    	for (int y = 0; y < ROWS; y++)
    		if (grd[x][y] == visited || grd[x][y] == path)
    		grd[x][y] = empty;
}

int bfs(grid grd, BFS_State *state) {
	if (isEmpty(&state->q) || state->finished == 1) return 0;

	int moveRow[] = {-1, 1, 0, 0};
	int moveCol[] = {0, 0, -1, 1};

	Node *current = peek(&state->q);
	Node next;
    dequeue(&state->q);

	for (int i=0;i<4;i++) {
		next.x = current->x + moveRow[i];
		next.y = current->y + moveCol[i];
		next.parent = current;
		if (next.x >= 0 && next.x < COLS && next.y >= 0 && next.y < ROWS) {
			Cell *nextCell = &grd[next.x][next.y];


			if (*nextCell == empty) {
				*nextCell = visited;
				enqueue(&state->q, next);
			}
			else if (*nextCell == end) {
				state->finished = 1;
			}
		}
	}
	if (grd[current->x][current->y] != start)
		grd[current->x][current->y] = visited;

	if (state->finished == 1) {
		while (grd[current->x][current->y] != start) {
    		grd[current->x][current->y] = path;
    		current = current->parent;
		}
		return 0;
	}
	else 
		return 1;
}