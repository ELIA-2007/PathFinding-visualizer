#include "queue.h"

typedef struct {
	int finished;
	queue q;
} BFS_State;

void initBFS(BFS_State *state, grid _grid, int startX, int startY);
int bfs(grid _grid, BFS_State *state);