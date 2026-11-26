#pragma once

#include "settings.h"
#include "input.h"
#include "grid.h"
#include "queue.h"
#include "priorityqueue.h"
#include "bfs.h"
#include "astar.h"
#include "font.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

typedef struct { //STRUCT THAT STORES EVERY VARIABLE (YES I LIKE C++ CLASSES)
    //SDL VIDEO VARIABLES
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    TTF_TextEngine *textEngine;


    //FIXED TEXTS
    char stepsBuffer[32];
    TTF_Text *algText;
    TTF_Text *algNameText;
    TTF_Text *stepsText;


    //TIME VARIABLES
    Uint64 lastStep;
    Uint64 stepDelay;


    //MACHINE VARIABLES
    int windowWidth, windowHeight, startX, startY, endX, endY, stepsNum;
    float cellWidth, cellHeight, mouseX, mouseY;
    BOOL running, puttingWalls, removingWalls, algRunning;


    //ALGORITHMS VARIABLES
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