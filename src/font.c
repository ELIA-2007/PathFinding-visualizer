#include "font.h"

void initText(TTF_TextEngine **engine, TTF_Font **font, SDL_Renderer **renderer) {
	*font = TTF_OpenFont("Caskaydia.ttf", 50.0f);
	*engine = TTF_CreateRendererTextEngine(*renderer);
}

void newText(TTF_TextEngine *engine, SDL_Renderer *renderer, TTF_Font *font,
			 char str[], int size, int r, int g, int b, int alpha, float x, float y) {
	
	TTF_Text *newTxt = TTF_CreateText(engine, font, str, 0);
	TTF_SetTextColor(newTxt, r, g, b, alpha);
	TTF_DrawRendererText(newTxt, x, y);
}