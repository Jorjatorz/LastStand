#pragma once

#include <string>
#include <vector>

#include "Vector3.h"
class Texture;
class Shader;

//Class that represents a material ingame
//"Compiled" means that the shader information has been send to the shader
//A material sends the basic data to the material shader (for example, constant color (or color obtained by simple mathematical operations), const rougness, etc). Complex operations (that uses textures, for example), mathematical functions, etc. should be done in the shader.
//By default
class FMaterial
{
public:
	FMaterial();
	~FMaterial();

	//Compiles and binds the shader
	void applyMaterialToStaticMesh();

	//Sets a new shader
	void setNewMaterialShader(std::string shaderName);
	Shader* const getMaterialShader();

	void setBaseColor(const Vector3& bColor);
	Vector3 getBaseColor();

	void setMetallicFactor(float factor);
	float getMetallicFactor();

	void setRoughnessFactor(float roughness);
	float getRoughnessFactor();

	void setEmissiveColor(const Vector3& eColor);
	Vector3 getEmissiveColor();

	void setOpacity(float opacity);
	float getOpacity();

	void setTextureForTheMaterial(std::string uniformSamplerName, Texture* texture);

	///TODO add the ability to send additional data, like deltaTime, etc

private:
	//All materials properties
	//Base Color
	Vector3 _baseColor;
	//Metallic
	float _metallic;
	//Specular
	//Roughness
	float _roughness;
	//Emissive Color
	Vector3 _emissiveColor;
	//Opacity
	float _opacity;
	//Opacity Mask
	//Normal
	//WorldPosition Offset
	//WorldDisplacement
	//Tessellation multiplayer
	//Subsurface color
	//Ambient occlusion
	//Refraction

	//List containing all the textures that will be send to the shader. The pair is made of the Texture and its sampler name in the shader
	std::vector<std::pair<std::string, Texture*>> _texturesInMaterialList;

	//Material shader pointer
	Shader* _shaderMaterialPtr;
	//True if the uniforms has been send
	bool _compiled;
	//Sends the uniform data to the shader
	void compileMaterial();
	//Sends all the global data (data that change per frame) to the shader
	void sendGlobalUniforms();
};

