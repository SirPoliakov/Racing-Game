#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Shader.h"
#include <vector>


class RendererOGL : public IRenderer
{
public:
	RendererOGL();
	virtual ~RendererOGL();
	RendererOGL(const RendererOGL&) = delete;
	RendererOGL& operator=(const RendererOGL&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void endDraw();
	void close();
	IRenderer::Type type() { return Type::OGL; }

	std::vector<class SpriteComponent*> getSprites() { return sprites; }
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprite(const class Actor& actor, const class Texture& tex, Flip flip) const;

private:
	
	void drawSprites();

	Window* window;
	SDL_GLContext context;
	VertexArray* spriteVertexArray;
	Matrix4 viewProj;

	std::vector<class SpriteComponent*> sprites;

};
