#include "machine.h"

BOOL initMachine(Machine *mcn) {
    *mcn = (Machine){0}; //INIT MACHINE
    //INIT BOOL VARIABLES
    mcn->stepDelay = STEP_DELAY;
    mcn->running = TRUE;
    mcn->puttingWalls = FALSE;
    mcn->removingWalls = FALSE;
    mcn->algRunning = FALSE;
    mcn->algorithm = ASTAR;
    mcn->lastStep = SDL_GetTicks();

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
             &mcn->cellWidth, &mcn->cellHeight, &mcn->startX, &mcn->startY, &mcn->endX, &mcn->endY);

    return 0;
}
void machineHandleEvents(Machine *mcn) { //HANDLE INPUTS
    SDL_Event event;
    SDL_GetMouseState(&mcn->mouseX, &mcn->mouseY);

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                mcn->running = FALSE;
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        mcn->puttingWalls = TRUE;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mcn->removingWalls = TRUE;
                        break;
                    default:
                        break;
                }
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        mcn->puttingWalls = FALSE;
                        break;
                    case SDL_BUTTON_RIGHT:
                        mcn->removingWalls = FALSE;
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
                        if (!mcn->algRunning) resetStartEndCells(mcn->grd, &mcn->startX, &mcn->startY, &mcn->endX, &mcn->endY);
                        break;
                    case SDLK_RETURN:
                        if (!mcn->algRunning) {
                            switch (mcn->algorithm) {
                                case BFS:
                                    initBFS(&mcn->stateBFS, mcn->grd, mcn->startX, mcn->startY);
                                    break;
                                case ASTAR:
                                    mcn->stateASTAR = (AstarState){0};
                                    initAstar(&mcn->stateASTAR, mcn->grd, mcn->startX, mcn->startY);
                                    break;
                                default:
                                    printf("No algorithm detected!\n");
                                    break;
                            }
                            mcn->algRunning = TRUE;
                            mcn->lastStep = SDL_GetTicks();
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
    if (mcn->algRunning) {
        Uint64 now = SDL_GetTicks();
        if (now - mcn->lastStep >= mcn->stepDelay) {
            switch (mcn->algorithm) {
                case BFS:
                    mcn->algRunning = bfs(mcn->grd, &mcn->stateBFS);
                    break;
                case ASTAR:
                    mcn->algRunning = aStar(mcn->grd, &mcn->stateASTAR, mcn->endX, mcn->endY);
                    break;
                default:
                    printf("No algorithm detected!\n");
                    break;
            }
            mcn->lastStep = now;
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