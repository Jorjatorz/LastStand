#pragma once

#include <string>
#include <unordered_map>
#include <queue>

#include "Vector3.h"
class Texture;
class Shader;
class Matrix4;

//Class that represents a material ingame
//"Compiled" means that the shader information has been send to the shader
//A material sends the basic data to the material shader (for example, constant color (or color obtained by simple mathematical operations), const rougness, etc). Complex operations (that uses textures, for example), mathematical functions, etc. should be done in the shader.
//By default
class FMaterial
{
public:
	FMaterial();
	~FMaterial();

	//Compiles and binds the shader. It sends material information uniforms and also per-frame uniforms like mesh matrices (model, normals), view matrix, projection matrix, etc.
	void sendMaterialInformationToGPU(const Matrix4& staticMesh_ModelMatrix);

	//Sets a new shader to the material. If the shader is not loaded yet it will be loaded.
	void setNewMaterialShader(std::string shaderName);
	Shader* const getMaterialShader();

	//Adds a texture sampler to send to the shader. It will be loaded (if not alrady) when the material is compiled
	//If a texture already exists with the same samplerName it will be overwritten by the new one.
	void setTextureForTheMaterial(std::string uniformSamplerName, std::string texturePath);
	//Adds a texture sampler to send to the shader. The texture is already laoded
	//If a texture already exists with the same samplerName it will be overwritten by the new one.
	void setTextureForTheMaterial(std::string uniformSamplerName, Texture* texture);
	//Sends float uniforms to the shader when the material is compiled. If the uniform alrady exists it updates the value.
	void addUniform_float(std::string uniformName, float value);
	//Sends vector uniforms to the shader when the material is compiled. If the uniform alrady exists it updates the value.
	void addUniform_vector3(std::string uniformName, Vector3 value);
	

private:
	//All materials uniforms to send
	std::unordered_map<std::string, float> _floatUniformsMap;
	std::unordered_map<std::string, Vector3> _vectorUniformsMap;
	//Queue holding the texture that will be loaded/get when the material is compiled
	std::queue<std::pair<std::string, std::string>> _texturesToCompile;
	//List containing all the textures that will be send to the shader. The pair is made of the Texture and its sampler name in the shader
	std::unordered_map<std::string, Texture*> _texturesInMaterialMap;

	//Material shader pointer
	Shader* _shaderMaterialPtr;
	//True if the uniforms has been send
	bool _compiled;
	//Sends the uniform data to the shader
	void compileMaterial();
	void sendTexturesToShader();
	void sendFloatsToShader();
	void sendVectorsToShader();
	//Sends all the per frame to the shader
	void sendPerFrameUniforms(const Matrix4& staticMesh_ModelMatrix);
};

