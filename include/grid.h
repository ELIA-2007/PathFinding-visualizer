#pragma once
#include "settings.h"
#include <SDL3/SDL.h>
#include <time.h>

typedef enum {
	empty,
	start,
	end,
	wall,
	visited,
	path
} cell;
typedef cell grid[COLS][ROWS];

void initGrid(grid _grid, int winWidth, int windHeight, float *cell_width, float *cell_height, int *startX, int *startY);
void drawGrid(grid _grid, SDL_Renderer *renderer, int windWidth, int windHeight, float cell_width, float cell_height);
void resetWalls(grid _grid);
void resetStartEndCells(grid _grid, int *startX, int *startY);
cell* checkMouseCell(grid _grid, int winWidth, int winHeight, float mouseX, float mouseY);