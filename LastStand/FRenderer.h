#pragma once

#include "Singleton.h"
#include "FDeferredFrameBuffer.h"
#include "FStaticMesh.h"

#include <gl/glew.h>

class FWorld;
class Matrix4;
class FScene;
class FCameraComponent;

//Class incharge of rendering all the FObjects in the world.
class FRenderer : public Singleton<FRenderer>
{
public:
	FRenderer(unsigned short int width, unsigned short int height);
	~FRenderer();

	FScene* const getCurrentFScene();

	//Main function. Renders all the objects in the worlds that are visible.
	void renderObjectsInTheWorld();

	const Matrix4& getCurrentFrameProjectionMatrix();
	const Matrix4& getCurrentFrameViewMatrix();
	const Vector3& getCurrentRenderingCameraWPosition();
private:
	//Deferred framebuffer
	FDeferredFrameBuffer* _gBuffer;

	//Do a normal deferred pass and fills the buffers and the rendering targets of the camera
	void doDeferredPass(FCameraComponent* currentCamera);
	void geometryPass();
	void lightPass();
	void UIPass();
	void finalPass();
	//Rendenders a Quad (with desired dimensions) and writes there the result of the deferred pass
	void drawToScreenQuad();
	FStaticMesh _screenQuadMesh;

	//Current frame matrix (updates per frame)
	Matrix4* _currentFrameProjectionM;
	Matrix4* _currentFrameViewM;
	Vector3 _currentRenderingCameraWPosition;

	//Current Scene to render
	FScene* _sceneToRender;
};

