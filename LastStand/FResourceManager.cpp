#include "FResourceManager.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include "FLog.h"

#include <assert.h>

FResourceManager::FResourceManager()
{
}


FResourceManager::~FResourceManager()
{
	//Delete all shaders
	for( auto &it : _shaderMap)
	{
		delete it.second;
	}
	_shaderMap.clear();
	//Delete all textures
	for (auto &it : _textureMap)
	{
		delete it.second;
	}
	_textureMap.clear();
	//Delete all mshes
	for (auto &it : _meshMap)
	{
		delete it.second;
	}
	_meshMap.clear();
}

Shader* FResourceManager::loadShaderIntoMemoryFromDisk(std::string shaderName)
{
	FLog(FLog::INFO, "Loading Shader " + shaderName);

	auto it = _shaderMap.find(shaderName);
	if (it != _shaderMap.end())
	{
		FLog(FLog::ERROR, "Can't load the shader into memory, it already exist: " + shaderName);
		assert(0);
	}

	//Create a new shader with a name(to identify it in the log)
	Shader* newShader = new Shader(shaderName);
	//Load the shader from a file
	if (newShader->loadFromDisk("Data\\Shaders\\" + shaderName))
	{
		FLog(FLog::INFO, shaderName + " shader loaded.");
		_shaderMap.emplace(std::make_pair(shaderName, newShader));
	}
	else
	{
		FLog(FLog::ERROR, "Couldn't load Shader: Data\\Shaders\\" + shaderName);
		delete newShader;
	}

	return newShader;

}
void FResourceManager::deleteShaderFromMemory(std::string shaderName)
{
	auto it = _shaderMap.find(shaderName);
	if (it == _shaderMap.end())
	{
		FLog(FLog::ERROR, "Can't delete the shader from memory, it doesnt exist: " + shaderName);
		assert(0);
	}

	delete it->second;
	_shaderMap.erase(it);
}
Shader* FResourceManager::getShaderInMemory(std::string shaderName)
{
	auto it = _shaderMap.find(shaderName);
	if (it == _shaderMap.end())
	{
		FLog(FLog::ERROR, "Can't return the shader in memory, it doesnt exist: " + shaderName);
		return NULL;
	}

	return it->second;
}

void FResourceManager::reloadAllShadersFromDisk()
{
	FLog(FLog::INFO, "Reloading all the shaders from its file");
	for(auto& it : _shaderMap)
	{
		it.second->loadFromDisk("Data\\Shaders\\" + it.first);
	}
}

Texture* FResourceManager::loadTextureIntoMemoryFromDisk(std::string textureName)
{
	FLog(FLog::INFO, "Loading Texture " + textureName);

	auto it = _textureMap.find(textureName);
	if (it != _textureMap.end())
	{
		FLog(FLog::ERROR, "Can't load the texture into memory, it already exists: " + textureName);
		assert(0);
	}

	Texture* newTexture = new Texture();
	//Load the texture from a file, by default with mipmap and RGBA format
	if (newTexture->loadFromDisk("Data\\Textures\\" + textureName, true, GL_RGBA))
	{
		_textureMap.emplace(std::make_pair(textureName, newTexture));
	}
	else
	{
		FLog(FLog::ERROR, "Couldn't load texture: Data\\Textures\\" + textureName);
		delete newTexture;
	}

	return newTexture;
}

Texture* FResourceManager::createNewTextureInMemory(std::string textureName, unsigned int width, unsigned int height, GLint format, bool mipmap)
{
	auto it = _textureMap.find(textureName);
	if (it != _textureMap.end())
	{
		FLog(FLog::ERROR, "Can't create the texture into memory, it already exists: " + textureName);
		assert(0);
	}

	Texture* newTexture = new Texture();
	//Generate the new texture without pixels
	newTexture->generateRawTexture(width, height, format, mipmap, NULL);

	_textureMap.emplace(std::make_pair(textureName, newTexture));

	FLog(FLog::INFO, "Texture Created: " + textureName);

	return newTexture;
}

void FResourceManager::deleteTextureFromMemory(std::string textureName)
{
	auto it = _textureMap.find(textureName);
	if (it == _textureMap.end())
	{
		FLog(FLog::ERROR, "Can't delete the texture from memory, it doesnt exist: " + textureName);
		assert(0);
	}

	delete it->second;
	_textureMap.erase(it);
}

Texture* FResourceManager::getTextureInMemory(std::string textureName)
{
	auto it = _textureMap.find(textureName);
	if (it == _textureMap.end())
	{
		FLog(FLog::ERROR, "Can't return the texture into memory, it doesnt exist: " + textureName);
		return NULL;
	}

	return it->second;
}

//Load a mesht into the memory
Mesh* FResourceManager::loadMeshIntoMemoryFromDisk(std::string meshName)
{
	FLog(FLog::INFO, "Loading Mesh " + meshName);

	auto it = _meshMap.find(meshName);
	if (it != _meshMap.end())
	{
		FLog(FLog::ERROR, "Mesh already into memory, can't load it " + meshName);
		assert(0);
	}

	Mesh* newMesh = new Mesh();
	//Load the mesh from a file
	if (newMesh->loadMesh("Data\\Meshes\\" + meshName))
	{
		FLog(FLog::INFO, meshName + " mesh loaded.");
		_meshMap.emplace(std::make_pair(meshName, newMesh));
	}
	else
	{
		FLog(FLog::ERROR, "Couldn't load mesh: Data\\Meshes\\" + meshName);
		delete newMesh;
	}

	return newMesh;
}
//Delete a mesh from memory
void FResourceManager::deleteMeshFromMemory(std::string meshName)
{
	auto it = _meshMap.find(meshName);
	if (it == _meshMap.end())
	{
		FLog(FLog::ERROR, "Can't delete the mesh from memory, it doesnt exist: " + meshName);
		assert(0);
	}

	delete it->second;
	_meshMap.erase(it);
}
//Return the mesh stored in meory
Mesh* FResourceManager::getMeshInMemory(std::string meshName)
{
	auto it = _meshMap.find(meshName);
	if (it == _meshMap.end())
	{
		FLog(FLog::ERROR, "Can't return the mesh in memory, it doesnt exist: " + meshName);
		return NULL;
	}

	return it->second;
}