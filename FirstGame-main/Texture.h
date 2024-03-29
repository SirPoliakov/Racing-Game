#pragma once
#include <string>

#include "RendererOGL.h"

using std::string;


class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool loadOGL(RendererOGL& rendererP, const string& filenameP);

	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);
	void setActive() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

	void createFromSurface(struct SDL_Surface* surface);

private:
	unsigned int textureID;
	string filename;
	int width;
	int height;
	SDL_Texture* SDLTexture = nullptr;
};
