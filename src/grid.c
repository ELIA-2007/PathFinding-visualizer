#include "grid.h"
#include <stdlib.h>
#include <stdio.h>

void resetWalls(grid _grid) {
	for (int x = 0; x < COLS; x++)
    	for (int y = 0; y < ROWS; y++)
    		if (_grid[x][y] == wall)
    		_grid[x][y] = empty;
}

void resetStartEndCells(grid _grid, int *startX, int *startY) {
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
	} while (_grid[start_x][start_y] == wall || _grid[end_x][end_y] == wall);

	for (int x = 0; x < COLS; x++)
    	for (int y = 0; y < ROWS; y++)
    		if (_grid[x][y] != wall)
    		_grid[x][y] = empty;

	_grid[start_x][start_y] = start;
    _grid[end_x][end_y] = end;
    *startX = start_x;
    *startY = start_y;
}

void initGrid(grid _grid, int windWidth, int windHeight, float *cell_width, float *cell_height, int *startX, int *startY) {
	//SCALE CELLS DIMENSION
	*cell_width = windWidth * 0.8f / COLS;
	*cell_height = windHeight * 0.8f / ROWS;

	//INITIALIZE CELLS
    resetStartEndCells(_grid, startX, startY);
	resetWalls(_grid);
}

void drawGrid(grid _grid, SDL_Renderer *renderer, int windWidth, int windHeight, float cell_width, float cell_height) {
	//DRAW EACH CELL INDIVIDUALLY
	float deltaY = (windHeight - (windHeight * 0.8f)) / 2;
	for (int x = 0; x < COLS; x++) {
    	for (int y = 0; y < ROWS; y++) {

        SDL_FRect rect = {x * cell_width, y * cell_height + deltaY, cell_width, cell_height};

        //SET COLOR BASED ON CELLS IDENTITY
        if (_grid[x][y] == empty)
        	SDL_SetRenderDrawColor(renderer, 40, 40, 100, 255);
        else if (_grid[x][y] == start)
        	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        else if (_grid[x][y] == end)
        	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (_grid[x][y] == wall)
        	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        else if (_grid[x][y] == visited)
        	SDL_SetRenderDrawColor(renderer, 100, 40, 100, 255);
        else if (_grid[x][y] == path)
        	SDL_SetRenderDrawColor(renderer, 100, 180, 180, 255);
    	SDL_RenderFillRect(renderer, &rect);
    	}
	}

	//DRAW LINES
	for (int i=0;i<COLS;i++) {
		SDL_FRect line = {(float)i * cell_width, 0 + deltaY, 3.0f, windHeight - 2 * deltaY};
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	SDL_RenderFillRect(renderer, &line);
	}
	for (int i=0;i<ROWS;i++) {
		SDL_FRect line = {0, (float)i * cell_height + deltaY, windWidth * 0.8f, 3.0f};
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	SDL_RenderFillRect(renderer, &line);
	}
}

cell* checkMouseCell(grid _grid, int windWidth, int windHeight, float mouseX, float mouseY) {
	cell *hovered;
	float deltaY = (windHeight - (windHeight * 0.8f)) / 2;
	if (mouseX > windWidth * 0.8f || mouseY < deltaY || mouseY > windHeight - deltaY)
		hovered = NULL;
	else {
		float cellX = mouseX / (windWidth * 0.8f / COLS);
		float cellY = (mouseY - deltaY) / (windHeight * 0.8f / ROWS);
		hovered = &_grid[(int)cellX][(int)cellY];
	}
	return hovered;
}