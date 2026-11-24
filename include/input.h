#pragma once
#include <SDL3/SDL.h>
#include "grid.h"


void putWalls(grid grd, float windowWidth, float windowHeight, float mouseX, float mouseY);
void removeWalls(grid grd, float windowWidth, float windowHeight, float mouseX, float mouseY);
void handleInputs(grid grd, float windowWidth, float windowHeight, float mouseX, float mouseY, int puttingWalls, int removingWalls);