#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Vector2.h"
#include "Matrix4.h"
#include "Shader.h"
#include "Texture.h"
#include "Rectangle.h"

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
	void drawSprite(const Matrix4 wrldTrans, const Texture& tex, Rectangle srcRect, Vector2 origin) const;
	void endDraw();

	void close();
	IRenderer::Type type() { return Type::OGL; }
	

private:

	Shader* shader;
	Window* window;
	VertexArray* vertexArray;
	SDL_GLContext context;
	Matrix4 viewProj;

};

