#pragma once
#include "IRenderer.h"
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"

class RendererSDL : public IRenderer
{
public:
	RendererSDL();
	virtual ~RendererSDL();


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
	IRenderer::Type type() { return Type::SDL; }
	SDL_Renderer* getRendererSDL() { return SDLRenderer; }

	void close();

private:
	SDL_Renderer* SDLRenderer = nullptr;

	RendererSDL(const RendererSDL&) = delete;
	RendererSDL& operator=(const RendererSDL&) = delete;
};