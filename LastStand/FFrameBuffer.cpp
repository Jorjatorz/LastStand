#include "FFrameBuffer.h"

#include "FEngine.h"
#include "FResourceManager.h"
#include "Texture.h"

FFrameBuffer::FFrameBuffer(std::string name, int width, int height)
	:_name(name),
	_width(width),
	_height(height),
	_binded(false)
{
	//Create the framebuffer in the constructor
	glGenFramebuffers(1, &_frameBufferId);
}

FFrameBuffer::~FFrameBuffer()
{
	glDeleteFramebuffers(1, &_frameBufferId);
}

void FFrameBuffer::addTexture(std::string textureName, GLint format)
{
	//Create the new texture, by deafult no mipmap
	Texture* texture = FResourceManager::getInstance()->createNewTextureInMemory(textureName, _width, _height, format, false);
	_texturePointersMap.emplace(textureName, texture);

	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _texturePointersMap.size() - 1, GL_TEXTURE_2D, texture->getTextureId(), 0); //mTextureMap.size() - 1 Because we want to start at 0
}

void FFrameBuffer::bindForDrawingToTextures()
{
	bindFrameBuffer();

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

void FFrameBuffer::bindTextures(int idStart)
{
	//Detach any binded frame buffer
	unBindFrameBuffer();

	int i = 0;
	for(auto& it : _texturePointersMap)
	{
		glActiveTexture(GL_TEXTURE0 + i + idStart);
		glBindTexture(GL_TEXTURE_2D, it.second->getTextureId());
		i++;
	}
}

void FFrameBuffer::bindFrameBuffer()
{
	if (!_binded)
		glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);

	_binded = true;
}

void FFrameBuffer::unBindFrameBuffer()
{
	if (_binded)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	_binded = false;
}

Texture* FFrameBuffer::getFrameBufferTexture(std::string textureName)
{
	return _texturePointersMap.find(textureName)->second;
}