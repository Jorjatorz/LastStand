#pragma once

#include <string>

#include "FrameBuffer.h"
#include "SingleInstance.h"

//FrameBuffer for deferred pass. Only one can be created
class DeferredFrameBuffer: public FrameBuffer, SingleInstance<DeferredFrameBuffer>
{
public:
	DeferredFrameBuffer(std::string name, int width, int height);
	~DeferredFrameBuffer();

	//Binds the textures that needs to be modified in the geometry pass (special call of the inherited function bindTexturesForDrawing)
	void bindForGeometryPass();
	//Binds the textures that need to be modified in the light pass
	void bindForLightPass();


private:
	//Depth texture id
	GLuint depthTextureId;

};

