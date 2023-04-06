#pragma once
#include <string>
#include <SDL.h>

using std::string;

class Texture
{
public:
	Texture();
	~Texture();
	
	bool loadOGL(const string& filenameP);
	void unload();
	//bool loadSDL(RendererSDL& rendererP, const string& filenameP);
	

	SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);
	void setActive() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	unsigned int textureID;
	string filename;
	int width;
	int height;
	SDL_Texture* SDLTexture = nullptr;
};

