#pragma once

#include "settings.h"
#include "input.h"
#include "grid.h"
#include "queue.h"
#include "priorityqueue.h"
#include "bfs.h"
#include "astar.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

typedef struct { //STRUCT THAT STORES EVERY VARIABLE (YES I LIKE C++ CLASSES)
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint64 lastStep;
    Uint64 stepDelay;

    int windowWidth, windowHeight, startX, startY, endX, endY;
    float cellWidth, cellHeight, mouseX, mouseY;
    BOOL running, puttingWalls, removingWalls, algRunning;

    grid grd;
    Algorithm algorithm;
    BFSState stateBFS;
    AstarState stateASTAR;
} Machine;

//FUNCTIONS
BOOL initMachine(Machine *mcn);
void machineHandleEvents(Machine *mcn);
void machineUpdate(Machine *mcn);
void machineRender(Machine *mcn);
void machineClear(Machine *mcn);