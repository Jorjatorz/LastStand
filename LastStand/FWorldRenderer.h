#pragma once

#include "SingleInstance.h"
#include "DeferredFrameBuffer.h"

#include <gl/glew.h>

class FWorld;
class Matrix4;
class Shader;

//Class incharge of rendering all the FObjects in the world.
class FWorldRenderer
{
public:
	FWorldRenderer(unsigned short int width, unsigned short int height);
	~FWorldRenderer();


	//Main function. Renders all the objects in the worlds that are visible.
	void renderObjectsInTheWorld(FWorld* currentWorld, const Matrix4& projectionViewMatrix);

private:
	//Deferred framebuffer
	DeferredFrameBuffer* _gBuffer;
	Shader* _deferredShader_combinationPass;

	//Rendenders a Quad (with desired dimensions) and writes there the result of the deferred pass
	void drawToScreenQuad(float startX, float startY, float endX, float endY);
	GLuint screenQuadVAO, screenQuadVBO; //ScreenQuad variables
};

