#include <SDL.h>
#include <iostream>
#include "Renderer.h"


Renderer::Renderer() : window(NULL), screenSurface(NULL)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("Group A", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);

			//Changes the screen background colour
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
			ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
			SDL_UpdateWindowSurface(window);

		}

	}
}


Renderer::~Renderer()
{
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Renderer::ClearScreen()
{
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}

void Renderer::renderPresent()
{
	SDL_RenderPresent(ren);
}

void Renderer::Draw(SDL_Texture *sprite, SDL_Rect *rect)
{
	SDL_RenderCopy(ren, sprite, NULL, rect);
}


void Renderer::Draw(SDL_Rect *rect)
{
	SDL_RenderFillRect(ren, rect);
}

void Renderer::DrawSprite(SDL_Texture *texture, SDL_Rect rcSrc, SDL_Rect rcSprite)
{
	SDL_RenderCopy(ren, texture, &rcSrc, &rcSprite);
}

void Renderer::LoadAssets()
{

}

SDL_Window * Renderer::GetWindow()
{
	return window;
}

SDL_Surface * Renderer::GetScreenSurface()
{
	return screenSurface;
}


SDL_Renderer* Renderer::GetRenderer()
{
	return ren;
}

int Renderer::GetScreenWidth()
{
	return SCREEN_WIDTH;
}
