#pragma once

#include <string>

#include <gl/glew.h>
#include <gl/gl.h>

#include "FreeImage.h"

//Class that load and handles a skin inside the engine
class Texture
{
public:
	Texture(void);
	~Texture(void);

	//Load a texture from a file, false if an error ocurred
	///Could make tis static
	bool loadFromDisk(std::string texturePath, bool mipmap, GLint format);
	//Generates a texture into memory. (Not loaded from file)
	void generateRawTexture(unsigned int width, unsigned int height, GLint format, bool mipmap, const GLvoid* pixels);
	//Update the current texture to have this new parameters
	void updateTexture(int width, int height, GLint format, bool mipmap, const GLvoid* pixels);

	//Return the texture opengl id
	GLuint getTextureId()
	{
		return _textureID;
	}

private:
	//is mipmap
	bool _isMipmap;
	//Texture format
	GLint _format;
	//Texture dimensions
	unsigned int _width, _height;
	//texture ID
	GLuint _textureID;


};
