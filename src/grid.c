#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
//GET COLOR BASED ON CELL TYPE
static SDL_Color cellColor(Cell c) {
    switch (c) {
        case start:   return (SDL_Color){0, 255, 0, 255};
        case end:     return (SDL_Color){255, 0, 0, 255};
        case wall:    return (SDL_Color){200, 200, 200, 255};
        case visited: return (SDL_Color){100, 40, 100, 255};
        case path:    return (SDL_Color){100, 180, 180, 255};
        case empty:
        default:      return (SDL_Color){40, 40, 100, 255};
    }
}

void resetWalls(grid grd) {
	for (int x = 0; x < COLS; x++)
    	for (int y = 0; y < ROWS; y++)
    		if (grd[x][y] == wall)
    		grd[x][y] = empty;
}

void resetVisited(grid grd) {
	for (int x = 0; x < COLS; x++)
    	for (int y = 0; y < ROWS; y++)
    		if (grd[x][y] == visited || grd[x][y] == path)
    		grd[x][y] = empty;
}
//CHOSE OTHER RANDOM STARTING AND ENDING CELLS
void resetStartEndCells(grid grd, int *startX, int *startY, int *endX, int *endY) {
	//RANDOMIZE START AND END CELLS
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	do {
	start_x = rand() % COLS;
	start_y = rand() % ROWS;
	end_x = rand() % COLS;
	end_y = rand() % ROWS;
	} while (grd[start_x][start_y] == wall || grd[end_x][end_y] == wall); //START AND END CAN'T BE WALLS

	for (int x = 0; x < COLS; x++)
    	for (int y = 0; y < ROWS; y++)
    		if (grd[x][y] != wall)
    		grd[x][y] = empty;

	grd[start_x][start_y] = start;
    grd[end_x][end_y] = end;
    *startX = start_x;
    *startY = start_y;
    *endX = end_x;
    *endY = end_y;
}

void initGrid(grid grd, int windWidth, int windHeight, float *cellWidth, float *cellHeight, int *startX, int *startY, int *endX, int *endY) {
	//SCALE CELLS DIMENSION
	*cellWidth = windWidth * 0.8f / COLS;
	*cellHeight = windHeight * 0.8f / ROWS;

	//INITIALIZE CELLS
    resetStartEndCells(grd, startX, startY, endX, endY);
	resetWalls(grd);
}
//DRAW
void drawGrid(grid grd, SDL_Renderer *renderer, int windWidth, int windHeight, float cellWidth, float cellHeight) {
	//DRAW EACH CELL INDIVIDUALLY
	float deltaY = (windHeight - (windHeight * 0.8f)) / 2;
	for (int x = 0; x < COLS; x++) {
    	for (int y = 0; y < ROWS; y++) {

        SDL_FRect rect = {x * cellWidth, y * cellHeight + deltaY, cellWidth, cellHeight};

        //SET COLOR BASED ON CELLS TYPES AND DRAW
        SDL_Color col = cellColor(grd[x][y]);
        SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    	SDL_RenderFillRect(renderer, &rect);
    	}
	}

	//DRAW GRID LINES
	for (int i=0;i<COLS;i++) {
		SDL_FRect line = {(float)i * cellWidth, 0 + deltaY, 3.0f, windHeight - 2 * deltaY};
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	SDL_RenderFillRect(renderer, &line);
	}
	for (int i=0;i<ROWS;i++) {
		SDL_FRect line = {0, (float)i * cellHeight + deltaY, windWidth * 0.8f, 3.0f};
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	SDL_RenderFillRect(renderer, &line);
	}
}
//RETURN CELL HOVERED BY MOUSE
Cell* checkMouseCell(grid grd, int windWidth, int windHeight, float mouseX, float mouseY) {
	Cell *hovered;
	float deltaY = (windHeight - (windHeight * 0.8f)) / 2;
	if (mouseX > windWidth * 0.8f || mouseY < deltaY || mouseY > windHeight - deltaY)
		hovered = NULL;
	else {
		float cellX = mouseX / (windWidth * 0.8f / COLS);
		float cellY = (mouseY - deltaY) / (windHeight * 0.8f / ROWS);
		hovered = &grd[(int)cellX][(int)cellY];
	}
	return hovered;
}