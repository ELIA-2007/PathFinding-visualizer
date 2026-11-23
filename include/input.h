#pragma once
#include <SDL3/SDL.h>
#include "grid.h"


void putWalls(grid _grid, float windowWidth, float windowHeight, float mouseX, float mouseY);
void removeWalls(grid _grid, float windowWidth, float windowHeight, float mouseX, float mouseY);
void handleInputs(grid _grid, float windowWidth, float windowHeight, float mouseX, float mouseY, int puttingWalls, int removingWalls);