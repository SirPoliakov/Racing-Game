#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "Vector2.h"

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

	// loadConcreteText();
	// loadCarText();
	// loadTreeText();

	//void draw();
	void endDraw();

	

	void close();
	IRenderer::Type type() { return Type::OGL; }

private:

	Window* window;
	VertexArray* vertexArray;
	SDL_GLContext context;

};

