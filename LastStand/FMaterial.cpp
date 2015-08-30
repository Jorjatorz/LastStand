#include "FMaterial.h"

#include "Vector3.h"
#include "Texture.h"
#include "Shader.h"
#include "Matrix4.h"
#include "FResourceManager.h"
#include "FRenderer.h"
#include "FEngine.h"
#include "TimerManager.h"

FMaterial::FMaterial()
	:_compiled(false)
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
	if (!_shaderMaterialPtr)
	{
		_shaderMaterialPtr = FResourceManager::getInstance()->loadShaderIntoMemoryFromDisk(shaderName);
	}
	_compiled = false;
}

Shader* const FMaterial::getMaterialShader()
{
	return _shaderMaterialPtr;
}

void FMaterial::sendMaterialInformationToGPU(const Matrix4& staticMesh_ModelMatrix)
{
	_shaderMaterialPtr->bind();
	sendPerFrameUniforms(staticMesh_ModelMatrix);

	if (!_compiled)
	{
		compileMaterial();
	}
}

void FMaterial::compileMaterial()
{
	//Send uniforms
	sendFloatsToShader();
	sendVectorsToShader();
	sendTexturesToShader();

	_compiled = true;

}

void FMaterial::sendPerFrameUniforms(const Matrix4& staticMesh_ModelMatrix)
{
	_shaderMaterialPtr->uniformMatrix("Renderer_ProjectionMatrix", FRenderer::getInstance()->getCurrentFrameProjectionMatrix());
	_shaderMaterialPtr->uniformMatrix("Renderer_ViewMatrix", FRenderer::getInstance()->getCurrentFrameViewMatrix());
	_shaderMaterialPtr->uniformMatrix("Renderer_ModelViewProjectionMatrix", FRenderer::getInstance()->getCurrentFrameProjectionMatrix() * FRenderer::getInstance()->getCurrentFrameViewMatrix() * staticMesh_ModelMatrix);

	_shaderMaterialPtr->uniformMatrix("Renderer_ModelMatrix", staticMesh_ModelMatrix);
	_shaderMaterialPtr->uniformMatrix("Renderer_NormalMatrix", staticMesh_ModelMatrix.getInverseTransposeMatrix());

	_shaderMaterialPtr->uniform("Engine_totalTime", TimerManager::getTotalExecutionTime() / 1000.0f);
}

void FMaterial::sendFloatsToShader()
{
	for (const auto& it : _floatUniformsMap)
	{
		_shaderMaterialPtr->uniform(it.first, it.second);
	}
}

void FMaterial::sendVectorsToShader()
{
	for (const auto& it : _vectorUniformsMap)
	{
		_shaderMaterialPtr->uniform(it.first, it.second);
	}
}

void FMaterial::sendTexturesToShader()
{
	//Load/Get the textures
	while (!_texturesToCompile.empty())
	{
		Texture* tex = FResourceManager::getInstance()->getTextureInMemory(_texturesToCompile.front().second);
		if (!tex)
		{
			tex = FResourceManager::getInstance()->loadTextureIntoMemoryFromDisk(_texturesToCompile.front().second);
		}

		_texturesInMaterialMap.insert(std::make_pair(_texturesToCompile.front().first, tex));

		_texturesToCompile.pop();
	}
	//Send all textures
	int i = 0; //Set a valid active texture slot
	for (auto const &it : _texturesInMaterialMap)
	{
		it.second->bindTexture(i);
		_shaderMaterialPtr->uniformTexture(it.first, i);
		i++;
	}

}

void FMaterial::setTextureForTheMaterial(std::string uniformSamplerName, std::string texturePath)
{
	//If two textures has the same sampler name the shader will take the last added one
	_texturesToCompile.push(std::pair<std::string, std::string>(uniformSamplerName, texturePath));

	_compiled = false;
}

void FMaterial::addUniform_float(std::string uniformName, float value)
{
	_floatUniformsMap[uniformName] = value;

	_compiled = false;
}

void FMaterial::addUniform_vector3(std::string uniformName, Vector3 value)
{
	_vectorUniformsMap[uniformName] = value;

	_compiled = false;
}