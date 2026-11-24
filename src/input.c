#include "input.h"

void putWalls(grid grd, float windowWidth, float windowHeight, float mouseX, float mouseY) {
	Cell *hovered = checkMouseCell(grd, windowWidth, windowHeight, mouseX, mouseY);
    if (hovered != NULL && *hovered == empty)
        *hovered = wall;
}
void removeWalls(grid grd, float windowWidth, float windowHeight, float mouseX, float mouseY) {
	Cell *hovered = checkMouseCell(grd, windowWidth, windowHeight, mouseX, mouseY);
    if (hovered != NULL && *hovered == wall)
        *hovered = empty;
}
void handleInputs(grid grd,
				  float windowWidth, float windowHeight,
				  float mouseX, float mouseY,
				  int puttingWalls, int removingWalls) {
	if (puttingWalls)
		putWalls(grd, windowWidth, windowHeight, mouseX, mouseY);
	else if (removingWalls)
		removeWalls(grd, windowWidth, windowHeight, mouseX, mouseY);
}