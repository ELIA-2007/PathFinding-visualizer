#include "input.h"

void putWalls(grid _grid, float windowWidth, float windowHeight, float mouseX, float mouseY) {
	cell *hovered = checkMouseCell(_grid, windowWidth, windowHeight, mouseX, mouseY);
    if (hovered != NULL && *hovered == empty)
        *hovered = wall;
}
void removeWalls(grid _grid, float windowWidth, float windowHeight, float mouseX, float mouseY) {
	cell *hovered = checkMouseCell(_grid, windowWidth, windowHeight, mouseX, mouseY);
    if (hovered != NULL && *hovered == wall)
        *hovered = empty;
}
void handleInputs(grid _grid,
				  float windowWidth, float windowHeight,
				  float mouseX, float mouseY,
				  int puttingWalls, int removingWalls) {
	if (puttingWalls)
		putWalls(_grid, windowWidth, windowHeight, mouseX, mouseY);
	else if (removingWalls)
		removeWalls(_grid, windowWidth, windowHeight, mouseX, mouseY);
}