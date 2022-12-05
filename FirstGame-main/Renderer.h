#pragma once
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"

class Renderer
{
public:
	Renderer();
	bool initialize(Window& window);

	void beginDraw();
	void drawRectRed(Rectangle& rect);
	void drawRectWhite(Rectangle& rect);
	void drawRectRandom(Rectangle& rect, const int r, const int g, const int b);
	SDL_Texture* loadConcreteText();
	SDL_Texture* loadCarText();
	SDL_Texture* loadTreeText();
	void drawImage(Rectangle& rect, SDL_Texture* text, double ang);
	void endDraw();
	SDL_Renderer* getRenderer();

	void close();

private:
	SDL_Renderer* SDLRenderer;

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
};