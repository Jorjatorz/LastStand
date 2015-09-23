#include "FDeferredFrameBuffer.h"

#include "FEngine.h"
#include "Texture.h"

FDeferredFrameBuffer::FDeferredFrameBuffer(std::string name, int width, int height)
	:FFrameBuffer(name, width, height)
{
	//Create the textures
	//Color Texture. Attachment 0
	addTexture("DeferredFrameBufferText_Color", GL_RGBA); //8 bits per component
	//Color Texture. Attachment 1
	addTexture("DeferredFrameBufferText_Emissive", GL_RGBA); //8 bits per component
	//Normal Texture. Attachment 2
	///TODO - Make this more efficient enconding -- http://aras-p.info/texts/CompactNormalStorage.html
	addTexture("DeferredFrameBufferText_Normals", GL_RGBA16F); //High precision for normals and position. 16 bits per component
	//Normal Texture. Attachment 3
	addTexture("DeferredFrameBufferText_Position", GL_RGBA16F);
	//Light Texture. Attachment 4
	addTexture("DeferredFrameBufferText_Light", GL_RGBA);
	//Final Texture. Attachment 5
	addTexture("DeferredFrameBufferText_Final", GL_RGBA);

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
}


FDeferredFrameBuffer::~FDeferredFrameBuffer()
{
	glDeleteTextures(1, &depthTextureId);
}

void FDeferredFrameBuffer::bindForGeometryPass()
{
	bindFrameBuffer();

	GLuint geometryAttachments[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3}; //Bind color and normals texture
	//Draw to buffers
	glDrawBuffers(4, geometryAttachments);
}

void FDeferredFrameBuffer::bindForLightPass()
{
	bindFrameBuffer();

	GLuint lightAttachments[] = {GL_COLOR_ATTACHMENT4}; //Bind light texture
	//Draw to buffer
	glDrawBuffers(1, lightAttachments);
}

void FDeferredFrameBuffer::bindForFinalPass()
{
	bindFrameBuffer();

	GLuint finalAttachment[] = { GL_COLOR_ATTACHMENT5}; //Bind light texture
	//Draw to buffer
	glDrawBuffers(1, finalAttachment);
}

