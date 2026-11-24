#include "machine.h"

BOOL initMachine(Machine *mcn) {
    *mcn = (Machine){0}; //INIT MACHINE
    //INIT BOOL VARIABLES
    mcn->stepDelay = STEP_DELAY;
    mcn->running = true;
    mcn->puttingWalls = false;
    mcn->removingWalls = false;
    mcn->BFSRunning = false;

    srand((unsigned int)time(NULL)); //SET RANDOM SEED

    //INIT SDL3 VIDEO
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Errore SDL_Init: %s", SDL_GetError());
        return 1;
    }
    //CREATE WINDOW
    if (!SDL_CreateWindowAndRenderer("PathFinding", 0, 0, SDL_WINDOW_FULLSCREEN,
                                     &mcn->window, &mcn->renderer)) {
        SDL_Log("Errore finestra: %s", SDL_GetError());
        return 2;
    }
    //SCALE BASED ON DISPLAY SIZE
    SDL_GetWindowSize(mcn->window, &mcn->windowWidth, &mcn->windowHeight);
    initGrid(mcn->grd, mcn->windowWidth, mcn->windowHeight,
             &mcn->cellWidth, &mcn->cellHeight, &mcn->startX, &mcn->startY);

    mcn->lastBFS = SDL_GetTicks();
    return 0;
}
void machineHandleEvents(Machine *mcn) { //HANDLE INPUTS
    SDL_Event event;
    SDL_GetMouseState(&mcn->mouseX, &mcn->mouseY);

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                mcn->running = false;
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        mcn->puttingWalls = true;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mcn->removingWalls = true;
                        break;
                    default:
                        break;
                }
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        mcn->puttingWalls = false;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mcn->removingWalls = false;
                        break;
                    default:
                        break;
                }
                break;

            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                    case SDLK_BACKSPACE:
                        resetWalls(mcn->grd);
                        break;
                    case SDLK_SPACE:
                        resetStartEndCells(mcn->grd, &mcn->startX, &mcn->startY);
                        break;
                    case SDLK_RETURN:
                        if (!mcn->BFSRunning) {
                            initBFS(&mcn->stateBFS, mcn->grd, mcn->startX, mcn->startY);
                            mcn->BFSRunning = true;
                            mcn->lastBFS = SDL_GetTicks();
                        }
                        break;
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }

    handleInputs(mcn->grd, mcn->windowWidth, mcn->windowHeight,
                 mcn->mouseX, mcn->mouseY, mcn->puttingWalls, mcn->removingWalls);
}
//UPDATE GAME TICKS AND ALGORITHM STEPS
void machineUpdate(Machine *mcn) {
    if (mcn->BFSRunning) {
        Uint64 now = SDL_GetTicks();
        if (now - mcn->lastBFS >= mcn->stepDelay) {
            mcn->BFSRunning = bfs(mcn->grd, &mcn->stateBFS);
            mcn->lastBFS = now;
        }
    }
}
//RENDER EVERYTHING HERE
void machineRender(Machine *mcn) {
    SDL_SetRenderDrawColor(mcn->renderer, 0, 0, 0, 255);
    SDL_RenderClear(mcn->renderer);
    drawGrid(mcn->grd, mcn->renderer, mcn->windowWidth, mcn->windowHeight,
             mcn->cellWidth, mcn->cellHeight);
    SDL_RenderPresent(mcn->renderer);
}
//CLEAR
void machineClear(Machine *mcn) {
    if (mcn->renderer) {
        SDL_DestroyRenderer(mcn->renderer);
        mcn->renderer = NULL;
    }
    if (mcn->window) {
        SDL_DestroyWindow(mcn->window);
        mcn->window = NULL;
    }
    SDL_Quit();
}