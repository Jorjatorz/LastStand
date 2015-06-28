#pragma once

#include "Singleton.h"
#include "FDeferredFrameBuffer.h"

#include <gl/glew.h>

class FWorld;
class Matrix4;
class Shader;
class FScene;

//Class incharge of rendering all the FObjects in the world.
class FRenderer : public Singleton<FRenderer>
{
public:
	FRenderer(unsigned short int width, unsigned short int height);
	~FRenderer();

	FScene* const getCurrentFScene();

	//Main function. Renders all the objects in the worlds that are visible.
	void renderObjectsInTheWorld(FWorld* currentWorld, const Matrix4& projectionMatrix, const Matrix4& viewMatrix);

	const Matrix4& getCurrentFrameProjectionMatrix();
	const Matrix4& getCurrentFrameViewMatrix();
private:
	//Deferred framebuffer
	FDeferredFrameBuffer* _gBuffer;
	Shader* _deferredShader_combinationPass;

	//Rendenders a Quad (with desired dimensions) and writes there the result of the deferred pass
	void drawToScreenQuad(float startX, float startY, float endX, float endY);
	GLuint screenQuadVAO, screenQuadVBO; //ScreenQuad variables

	//Current frame matrix (updates per frame)
	const Matrix4*  _currentFrameProjectionM;
	const Matrix4* _currentFrameViewM;

	//Current Scene to render
	FScene* _sceneToRender;
};

