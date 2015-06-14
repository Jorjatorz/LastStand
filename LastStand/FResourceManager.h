#pragma once

#include <unordered_map>

#include <gl/glew.h>

class Mesh;
class Shader;
class Texture;

//Class that manage all external resources that are added to the game.
class FResourceManager
{
public:
	FResourceManager();
	~FResourceManager();

	//Load a new shader into the memory
	Shader* loadShaderIntoMemoryFromDisk(std::string shaderName);
	//Delete the shader stored in memory
	void deleteShaderFromMemory(std::string shaderName);
	//Return the shader stored in memory
	Shader* getShaderInMemory(std::string shaderName);
	//Reload all the shaders from his file
	void reloadAllShadersFromDisk();

	//Load a new Texture into the memory
	Texture* loadTextureIntoMemoryFromDisk(std::string textureName);
	//Creates a new Texture and store it in the memory
	Texture* createNewTextureInMemory(std::string textureName, unsigned int width, unsigned int height, GLint format, bool mipmap);
	//Delete the texture stored in memory
	void deleteTextureFromMemory(std::string textureName);
	//Return the texture stored in memory
	Texture* getTextureInMemory(std::string textureName);

	//Load a mesh into the memory
	Mesh* loadMeshIntoMemoryFromDisk(std::string meshName);
	//Delete a mesh from memory
	void deleteMeshFromMemory(std::string meshName);
	//Return the mesh stored in meory
	Mesh* getMeshInMemory(std::string meshName);

private:
	//Map containing all the shaders loaded
	std::unordered_map<std::string, Shader*> _shaderMap;
	//Map containing all the texture loaded
	std::unordered_map<std::string, Texture*> _textureMap;
	//Map containing all the meshes loaded
	std::unordered_map<std::string, Mesh*> _meshMap;
};

