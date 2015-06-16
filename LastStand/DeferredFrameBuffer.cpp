#include "DeferredFrameBuffer.h"

#include "FEngine.h"
#include "FResourceManager.h"

DeferredFrameBuffer::DeferredFrameBuffer(std::string name, int width, int height)
	:FrameBuffer(name, width, height)
{
	//Create the textures
	//Color Texture. Attachment 0
	addTexture("DeferredFrameBufferText_Color", GL_RGBA8);
	//Normal Texture. Attachment 1
	addTexture("DeferredFrameBufferText_Normals", GL_RGBA8);
	//Light Texture. Attachment 2
	addTexture("DeferredFrameBufferText_Light", GL_RGBA8);

	//Create the Depth texture
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Load the shader for the combination pass
	FEngine::getSingleton()->getResourceManagerPtr()->loadShaderIntoMemoryFromDisk("DeferredShading_Combination");
}


DeferredFrameBuffer::~DeferredFrameBuffer()
{
	glDeleteTextures(1, &depthTextureId);
}

void DeferredFrameBuffer::bindForGeometryPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
	GLuint geometryAttachments[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};

	//Draw to buffers
	glDrawBuffers(2, geometryAttachments);
}

void DeferredFrameBuffer::bindForLightPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
	GLuint lightAttachments[] = { GL_COLOR_ATTACHMENT2};

	//Draw to buffer
	glDrawBuffers(1, lightAttachments);
}

