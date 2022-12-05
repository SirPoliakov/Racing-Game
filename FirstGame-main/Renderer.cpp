#include "Renderer.h"
#include "Log.h"
#include <random>

Renderer::Renderer() : SDLRenderer(nullptr)
{
}

bool Renderer::initialize(Window& window)
{
	SDLRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLRenderer)
	{
		Log::error(LogCategory::Video, "Failed to create renderer");
		return false;
	}
	return true;
}

void Renderer::beginDraw()
{
	SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255);
	SDL_RenderClear(SDLRenderer);
}

void Renderer::endDraw()
{
	SDL_RenderPresent(SDLRenderer);
}

SDL_Renderer* Renderer::getRenderer()
{
	return SDLRenderer;
}

void Renderer::drawRectRed(Rectangle& rect)
{
	SDL_SetRenderDrawColor(SDLRenderer, 255, 0, 0, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

void Renderer::drawRectWhite(Rectangle& rect)
{
	SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}

void Renderer::drawRectRandom(Rectangle& rect, const int r, const int g, const int b)
{
	SDL_SetRenderDrawColor(SDLRenderer, r, g, b, 255);
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderFillRect(SDLRenderer, &SDLRect);
}
	
SDL_Texture* Renderer::loadCarText()
{
	SDL_Surface* surface = SDL_LoadBMP("rsc/Car.bmp");

	SDL_Texture* text = SDL_CreateTextureFromSurface(getRenderer(), surface);
	SDL_FreeSurface(surface);

	return text;
}

SDL_Texture* Renderer::loadTreeText()
{
	SDL_Surface* surface = SDL_LoadBMP("rsc/Tree.bmp");

	SDL_Texture* text = SDL_CreateTextureFromSurface(getRenderer(), surface);
	SDL_FreeSurface(surface);

	return text;
}

SDL_Texture* Renderer::loadConcreteText()
{
	SDL_Surface* surface = SDL_LoadBMP("rsc/concrete.bmp");

	SDL_Texture* text = SDL_CreateTextureFromSurface(getRenderer(), surface);
	SDL_FreeSurface(surface);

	return text;
}

void Renderer::drawImage(Rectangle& rect, SDL_Texture* text, double ang)
{
	SDL_Rect SDLRect = rect.toSDLRect();
	SDL_RenderCopyEx(SDLRenderer, text, NULL, &SDLRect, ang, NULL, SDL_FLIP_NONE);
}

void Renderer::close()
{
	SDL_DestroyRenderer(SDLRenderer);
}