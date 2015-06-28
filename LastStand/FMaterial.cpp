#include "FMaterial.h"

#include "Vector3.h"
#include "Texture.h"
#include "Shader.h"
#include "FResourceManager.h"ç
#include "FRenderer.h"
#include "FEngine.h"
#include "TimerManager.h"

FMaterial::FMaterial()
	:_baseColor(0.5), //Gray base color by default
	_metallic(0.0),
	_roughness(0.0),
	_emissiveColor(0.0),
	_opacity(1.0),
	_compiled(false)
{
	//Load the default material shader
	_shaderMaterialPtr = FResourceManager::getInstance()->getShaderInMemory("defaultMaterialShader");

	if (!_shaderMaterialPtr)
	{
		_shaderMaterialPtr = FResourceManager::getInstance()->loadShaderIntoMemoryFromDisk("defaultMaterialShader");
	}
}


FMaterial::~FMaterial()
{
}

void FMaterial::setNewMaterialShader(std::string shaderName)
{
	_shaderMaterialPtr = FResourceManager::getInstance()->getShaderInMemory(shaderName);
}

Shader* const FMaterial::getMaterialShader()
{
	return _shaderMaterialPtr;
}

void FMaterial::setBaseColor(const Vector3& bColor)
{
	_baseColor = bColor;
}

Vector3 FMaterial::getBaseColor()
{
	return _baseColor;
}

void FMaterial::setMetallicFactor(float factor)
{
	_metallic = factor;
}

float FMaterial::getMetallicFactor()
{
	return _metallic;
}

void FMaterial::setRoughnessFactor(float roughness)
{
	_roughness = roughness;
}

float FMaterial::getRoughnessFactor()
{
	return _roughness;
}

void FMaterial::setEmissiveColor(const Vector3& eColor)
{
	_emissiveColor = eColor;
}

Vector3 FMaterial::getEmissiveColor()
{
	return _emissiveColor;
}

void FMaterial::setOpacity(float opacity)
{
	_opacity = opacity;
}

float FMaterial::getOpacity()
{
	return _opacity;
}

void FMaterial::applyMaterialToStaticMesh()
{
	_shaderMaterialPtr->bind();
	sendGlobalUniforms();

	if (!_compiled)
	{
		compileMaterial();
	}
}

void FMaterial::compileMaterial()
{
	//Send uniforms
	_shaderMaterialPtr->uniform("Material_BaseColor", _baseColor);
	_shaderMaterialPtr->uniform("Material_Metallic", _metallic);
	_shaderMaterialPtr->uniform("Material_Roughness", _roughness);
	_shaderMaterialPtr->uniform("Material_EmissiveColor", _emissiveColor);
	///TODO -- Send opacity and handle it
	//Send all textures
	int i = 0; //Set a valid active texture slot
	for (auto const &it : _texturesInMaterialList)
	{
		it.second->bindTexture(i);
		_shaderMaterialPtr->uniformTexture(it.first, i);
		i++;
	}

	_compiled = true;

}

void FMaterial::sendGlobalUniforms()
{
	_shaderMaterialPtr->uniformMatrix("Renderer_ProjectionMatrix", FRenderer::getInstance()->getCurrentFrameProjectionMatrix());
	_shaderMaterialPtr->uniformMatrix("Renderer_ViewMatrix", FRenderer::getInstance()->getCurrentFrameViewMatrix());
	_shaderMaterialPtr->uniform("Engine_totalTime", (float)TimerManager::getTotalExecutionTime());
}

void FMaterial::setTextureForTheMaterial(std::string uniformSamplerName, Texture* texture)
{
	//If two textures has the same sampler name the shader will take the last added one
	_texturesInMaterialList.push_back(std::pair<std::string, Texture*>(uniformSamplerName, texture));
}
