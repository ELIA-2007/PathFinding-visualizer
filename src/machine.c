#include "machine.h"

BOOL initMachine(Machine *mcn) {
	*mcn = (Machine){0};
    mcn->stepDelay = STEP_DELAY;
    mcn->running = true;
    mcn->puttingWalls = false;
    mcn->removingWalls = false;
    mcn->BFSRunning = false;

    srand((unsigned int)time(NULL));

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Errore SDL_Init: %s", SDL_GetError());
        return 1;
    }
    if (!SDL_CreateWindowAndRenderer("PathFinding", 0, 0, SDL_WINDOW_FULLSCREEN,
    								 &mcn->window, &mcn->renderer)) {
        SDL_Log("Errore finestra: %s", SDL_GetError());
        return 2;
    }

    SDL_GetWindowSize(mcn->window, &mcn->windowWidth, &mcn->windowHeight);
    initGrid(mcn->grd, mcn->windowWidth, mcn->windowHeight,
    		 &mcn->cellWidth, &mcn->cellHeight, &mcn->startX, &mcn->startY);

    mcn->lastBFS = SDL_GetTicks();
    return 0;
}
void machineHandleEvents(Machine *mcn) {
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
            				initBFS(&mcn->BFSstate, mcn->grd, mcn->startX, mcn->startY);
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

void machineUpdate(Machine *mcn) {
	if (mcn->BFSRunning) {
		Uint64 now = SDL_GetTicks();
    	if (now - mcn->lastBFS >= mcn->stepDelay) {
        	mcn->BFSRunning = bfs(mcn->grd, &mcn->BFSstate);
        	mcn->lastBFS = now;
    	}
    }
}

void machineRender(Machine *mcn) {
	SDL_SetRenderDrawColor(mcn->renderer, 0, 0, 0, 255);
    SDL_RenderClear(mcn->renderer);
    drawGrid(mcn->grd, mcn->renderer, mcn->windowWidth, mcn->windowHeight,
             mcn->cellWidth, mcn->cellHeight);
    SDL_RenderPresent(mcn->renderer);
}

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