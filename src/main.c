#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "bfs.h"

int main() {
    srand(time(NULL));
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    grid GRID;
    int windowWidth;
    int windowHeight;
    float cell_width;
    float cell_height;

    float mouseX;
    float mouseY;

    int startX;
    int startY;
    
    BFS_State state;
    Uint64 lastBFSTime = 0;
    Uint64 STEP_DELAY = 40;
    int BFSRun = 0;

    int puttingWalls = 0;
    int removingWalls = 0;
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Errore SDL_Init: %s", SDL_GetError());
        return 1;
    }
    if (!SDL_CreateWindowAndRenderer("PathFinding", 0, 0, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Errore finestra: %s", SDL_GetError());
        return 2;
    }

    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    initGrid(GRID, windowWidth, windowHeight, &cell_width, &cell_height, &startX, &startY);

    Uint64 last_ticks = SDL_GetTicksNS();

    int running = 1;

    //GAME LOOP
    while (running) {
        SDL_GetMouseState(&mouseX, &mouseY);
        Uint64 now = SDL_GetTicksNS();
        float dt = (float)(now - last_ticks) / 1e9f;
        last_ticks = now;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.button.button == SDL_BUTTON_LEFT)
                    puttingWalls = 1;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    removingWalls = 1;

            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                if (event.button.button == SDL_BUTTON_LEFT)
                    puttingWalls = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    removingWalls = 0;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_BACKSPACE)
                    resetWalls(GRID);

                else if (event.key.key == SDLK_SPACE)
                    resetStartEndCells(GRID, &startX, &startY);

                else if (event.key.key == SDLK_RETURN && !BFSRun) {
                    initBFS(&state, GRID, startX, startY);
                    BFSRun = 1;
                }
            }
            if (event.type == SDL_EVENT_QUIT)
                running = 0;
        }

        handleInputs(GRID, windowWidth, windowHeight, mouseX, mouseY, puttingWalls, removingWalls);
        if (BFSRun) {
            if (now - lastBFSTime >= STEP_DELAY) {
                BFSRun = bfs(GRID, &state);
                lastBFSTime = now;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawGrid(GRID, renderer, windowWidth, windowHeight, cell_width, cell_height);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}