#pragma once
#define STEP_DELAY 1
#define TRUE 1
#define FALSE 0

#include "settings.h"
#include "input.h"
#include "grid.h"
#include "queue.h"
#include "bfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

typedef int BOOL;

typedef struct { //STRUCT THAT STORES EVERY VARIABLE (YES I LIKE C++ CLASSES)
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint64 lastBFS;
    Uint64 stepDelay;

    int windowWidth, windowHeight, startX, startY;
    float cellWidth, cellHeight, mouseX, mouseY;
    BOOL running, puttingWalls, removingWalls, BFSRunning;

    grid grd;
    BFSState stateBFS;
} Machine;

//FUNCTIONS
BOOL initMachine(Machine *mcn);
void machineHandleEvents(Machine *mcn);
void machineUpdate(Machine *mcn);
void machineRender(Machine *mcn);
void machineClear(Machine *mcn);