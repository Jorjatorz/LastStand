#include "Texture.h"

#include "FLog.h"

Texture::Texture()
	:_width(0),
	_height(0),
	_format(-1),
	_textureID(-1),
	_isMipmap(false)
{
}


Texture::~Texture()
{
	//Delete the openGL texture
	glDeleteTextures(1, &_textureID);
}

bool Texture::loadFromDisk(std::string texturePath, bool mipmap, GLint format)
{
	//FROM FREEIMAGE EXAMPLE
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(texturePath.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(texturePath.c_str());
	}
	//if still unknown, return failure
	if (fif == FIF_UNKNOWN)
	{
		FLog(FLog::ERROR, "Unknown format of texture, can't load it: " + texturePath);
		return false;
	}

	//check that the library has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
	{
		dib = FreeImage_Load(fif, texturePath.c_str());

		//if the image failed to load, return failure
		if (!dib)
		{
			return false;
		}

		FREE_IMAGE_COLOR_TYPE type = FreeImage_GetColorType(dib);
		//If it has no 32 bit color format convert to it
		if (FREE_IMAGE_COLOR_TYPE::FIC_RGBALPHA != type)
		{
			dib = FreeImage_ConvertTo32Bits(dib);
		}
	}

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
	{
		FLog(FLog::ERROR, "Error getting bits, width or height of texture: " + texturePath);
		return false;
	}

	//If the texture hasn't being already created create a new one, else update it
	if (_textureID = -1)
	{
		generateRawTexture(width, height, format, mipmap, bits);
	}
	else
	{
		updateTexture(width, height, format, mipmap, bits);
	}

	FLog(FLog::INFO, "Width: " + std::to_string(width) + " Height: " + std::to_string(height) + " Bytes: " + std::to_string(width * height * 4));

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	return true;

}

void Texture::generateRawTexture(unsigned int width, unsigned int height, GLint format, bool mipmap, const GLvoid* pixels)
{
	//Create the texture
	GLuint tex;
	glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels); //Free image loads in BGR

	if (mipmap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		_isMipmap = true;
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		_isMipmap = false;
	}

	_format = format;
	_width = width;
	_height = height;

	_textureID = tex;
}

void Texture::updateTexture(int width, int height, GLint format, bool mipmap, const GLvoid* pixels)
{
	//Just modify the texture information
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels); //Free image loads in BGR
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bindTexture(int activeTextureSlot /*= 0*/)
{
	glActiveTexture(GL_TEXTURE0 + activeTextureSlot);
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::unBindTexture(int activeTextureSlot /*= 0*/)
{
	glActiveTexture(GL_TEXTURE0 + activeTextureSlot);
	glBindTexture(GL_TEXTURE_2D, 0);
}
