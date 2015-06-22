#pragma once

#include <string>

#include "FFrameBuffer.h"
#include "SingleInstance.h"

//FrameBuffer for deferred pass. Only one can be created
class FDeferredFrameBuffer: public FFrameBuffer, SingleInstance<FDeferredFrameBuffer>
{
public:
	FDeferredFrameBuffer(std::string name, int width, int height);
	~FDeferredFrameBuffer();

	//Binds the textures that needs to be modified in the geometry pass (special call of the inherited function bindForDrawingToTextures)
	void bindForGeometryPass();
	//Binds the textures that need to be modified in the light pass
	void bindForLightPass();


private:
	//Depth texture id
	GLuint depthTextureId;

};

