#include "FrameBuffer.h"

#include "FEngine.h"
#include "FResourceManager.h"
#include "Texture.h"

FrameBuffer::FrameBuffer(std::string name, int width, int height)
{
	_name = name;
	_width = width;
	_height = height;

	//Create the framebuffer in the constructor
	glGenFramebuffers(1, &_frameBufferId);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &_frameBufferId);
}

void FrameBuffer::addTexture(std::string textureName, GLint format)
{
	//Create the new texture, by deafult no mipmap
	Texture* texture = FEngine::getSingleton()->getResourceManagerPtr()->createNewTextureInMemory(textureName, _width, _height, format, false);
	_texturePointersMap.emplace(textureName, texture);

	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _texturePointersMap.size() - 1, GL_TEXTURE_2D, texture->getTextureId(), 0); //mTextureMap.size() - 1 Because we want to start at 0
}

void FrameBuffer::bindForDrawingToTextures()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
	//Create a vector for storing the buffer color attachments, reserve space for all the textures attached to the buffer
	std::vector<GLuint> bufferAttachments;
	bufferAttachments.reserve(_texturePointersMap.size());
	
	for (size_t i = 0; i <= _texturePointersMap.size(); ++i)
	{
		bufferAttachments.push_back(GL_COLOR_ATTACHMENT0 + i);
	}
	//Set the buffer to draw
	glDrawBuffers(_texturePointersMap.size(), bufferAttachments.data());
}

void FrameBuffer::bindTextures(int idStart)
{
	//Detach any binded frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	int i = 0;
	for(auto it : _texturePointersMap)
	{
		glActiveTexture(GL_TEXTURE0 + i + idStart);
		glBindTexture(GL_TEXTURE_2D, it.second->getTextureId());
		i++;
	}
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
}

void FrameBuffer::unBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Texture* FrameBuffer::getFrameBufferTexture(std::string textureName)
{
	return _texturePointersMap.find(textureName)->second;
}