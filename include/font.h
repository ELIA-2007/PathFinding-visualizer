#pragma once
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

void initText(TTF_TextEngine **engine, TTF_Font **font, SDL_Renderer **renderer);
void newText(TTF_TextEngine *engine, SDL_Renderer *renderer, TTF_Font *font,
			 char str[], int size, int r, int g, int b, int alpha, float x, float y);