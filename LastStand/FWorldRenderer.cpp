#include "FWorldRenderer.h"

#include "Matrix4.h"
#include "FWorld.h"
#include "FObject.h"

FWorldRenderer::FWorldRenderer()
{
}


FWorldRenderer::~FWorldRenderer()
{
}

void FWorldRenderer::renderObjectsInTheWorld(FWorld* currentWorld, const Matrix4& projectionViewMatrix)
{
	//Render all objects into the buffers
	auto objectsList = currentWorld->getObjectsInWorldConstPtr();

	//Apply global uniforms to shader

	//Render all the visible objects into the gBuffers
	for (auto obj : *objectsList)
	{
		obj.second->renderComponentToGBuffer();
	}

	//Light Pass
}
