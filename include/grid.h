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
} Cell;
typedef Cell grid[COLS][ROWS];

static SDL_Color cellColor(Cell c);
void initGrid(grid grd, int winWidth, int windHeight, float *cellWidth, float *cellHeight, int *startX, int *startY);
void drawGrid(grid grd, SDL_Renderer *renderer, int windWidth, int windHeight, float cellWidth, float cellHeight);
void resetWalls(grid grd);
void resetStartEndCells(grid grd, int *startX, int *startY);
Cell* checkMouseCell(grid grd, int winWidth, int winHeight, float mouseX, float mouseY);