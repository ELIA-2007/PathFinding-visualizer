#include "machine.h"

static void switchAlgorithm(Algorithm *alg, TTF_Text *algName) {
    *alg = (*alg + 1) % 2;
    switch (*alg) {
        case ASTAR:
            TTF_SetTextString(algName, "ASTAR", 0);
            break;
        case BFS:
            TTF_SetTextString(algName, "BFS", 0);
            break;
        default:
            printf("No algorithm detected to show");
            break;
    }
}

BOOL initMachine(Machine *mcn) {
    //INIT MACHINE
    *mcn = (Machine){0};


    //INIT VARIABLES AT DEFAULT VALUES
    mcn->stepDelay = STEP_DELAY;
    mcn->lastStep = SDL_GetTicks();
    mcn->algorithm = BFS;
    mcn->running = TRUE;
    mcn->puttingWalls = FALSE;
    mcn->removingWalls = FALSE;
    mcn->algRunning = FALSE;
    mcn->stepsNum = 0;


    srand((unsigned int)time(NULL)); //SET RANDOM SEED


    //INIT SDL3 VIDEO
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Errore SDL_Init: %s", SDL_GetError());
        return 1;
    }
    //INIT SDL3 TEXT RENDERING
    TTF_Init();
    //CREATE WINDOW
    if (!SDL_CreateWindowAndRenderer("PathFinding", 0, 0, SDL_WINDOW_FULLSCREEN,
                                     &mcn->window, &mcn->renderer)) {
        SDL_Log("Errore finestra: %s", SDL_GetError());
        return 2;
    }
    //INIT TEXT ENGINE
    initText(&mcn->textEngine, &mcn->font, &mcn->renderer);


    //INIT TEXTS
    mcn->algText = TTF_CreateText(mcn->textEngine, mcn->font, "Algorithm: ", 0);
    TTF_SetTextColor(mcn->algText, 255, 255, 255, 255);

    mcn->algNameText = TTF_CreateText(mcn->textEngine, mcn->font, "BFS", 0);
    TTF_SetTextColor(mcn->algNameText, 255, 255, 255, 255);

    mcn->stepsText = TTF_CreateText(mcn->textEngine, mcn->font, "Steps: 0", 0);
    TTF_SetTextColor(mcn->algText, 255, 255, 255, 255);


    //SCALE BASED ON DISPLAY SIZE
    SDL_GetWindowSize(mcn->window, &mcn->windowWidth, &mcn->windowHeight);
    initGrid(mcn->grd, mcn->windowWidth, mcn->windowHeight,
             &mcn->cellWidth, &mcn->cellHeight,
             &mcn->startX, &mcn->startY,
             &mcn->endX, &mcn->endY);


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
                    case SDLK_A:
                        switchAlgorithm(&mcn->algorithm, mcn->algNameText);
                        break;
                    case SDLK_BACKSPACE:
                        resetWalls(mcn->grd);
                        break;
                    case SDLK_SPACE:
                        if (!mcn->algRunning) resetStartEndCells(mcn->grd, &mcn->startX, &mcn->startY, &mcn->endX, &mcn->endY);
                        break;
                    case SDLK_RETURN:
                        if (!mcn->algRunning) {
                            mcn->stepsNum = 0;
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
                    mcn->algRunning = bfs(mcn->grd, &mcn->stateBFS, &mcn->stepsNum);
                    break;
                case ASTAR:
                    mcn->algRunning = aStar(mcn->grd, &mcn->stateASTAR, mcn->endX, mcn->endY, &mcn->stepsNum);
                    break;
                default:
                    printf("No running algorithm detected!\n");
                    break;
            }
            snprintf(mcn->stepsBuffer, sizeof(mcn->stepsBuffer), "Steps: %d", mcn->stepsNum);
            TTF_SetTextString(mcn->stepsText, mcn->stepsBuffer, 0);
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


    TTF_DrawRendererText(mcn->algText, mcn->cellWidth * COLS * 1.02, mcn->windowHeight / 50);
    TTF_DrawRendererText(mcn->algNameText, mcn->cellWidth * COLS * 1.15, mcn->windowHeight / 50);
    TTF_DrawRendererText(mcn->stepsText, mcn->cellWidth * COLS * 1.02, mcn->windowHeight / 50 + 100);


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