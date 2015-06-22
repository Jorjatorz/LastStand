#pragma once

#include <string>
#include <unordered_map>

#include <gl/glew.h>

class Texture;

class FFrameBuffer
{
public:
	FFrameBuffer(std::string name, int width, int height);
	~FFrameBuffer();

	//Creates a new texture and link it to the buffer
	void addTexture(std::string textureName, GLint format);
	//Bind the buffer to write into the textures
	void bindForDrawingToTextures();
	//Bind the buffer textures
	void bindTextures(int idStart = 0); //Idstart is the start of the active texture (i.e if u bind several buffers at the same time this prevents the textures to use the same location)

	//Bind the framebuffer
	void bindFrameBuffer();
	//Unbind the framebuffer
	void unBindFrameBuffer();

	//Return the texture by the name, is the same as calling it from the resourceManager
	Texture* getFrameBufferTexture(std::string textureName);

protected:
	//OPENGL id of the the frame buffer
	GLuint _frameBufferId;
	//Identification name of the frame buffer
	std::string _name;
	//Size of the frame buffer, all the textures has this size
	int _width, _height;
	//Keeps track if the deferred buffer has been binded
	bool _binded;

	//Map holding all the framebuffer texture pointers for fast acces (Accesible also from the resourceManager)
	std::unordered_map<std::string, Texture*> _texturePointersMap;
};

