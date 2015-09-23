#include "FScene.h"

#include "FPrimitiveComponentProxy.h"
#include "FLightComponentProxy.h"
#include "FLog.h"
#include "FMaterial.h"
#include "Matrix4.h"
#include "FEngine.h"
#include "FPlayerController.h"

FScene::FScene()
{
	//Load light meshes
	_directionalLightVolume.setNewMesh("UnitQuad.obj");
	_pointLightVolume.setNewMesh("PointLVolume.obj");
// 	_spotLightVolume = rManager->loadMeshIntoMemoryFromDisk("SpotLVolume.obj");
	//Set material to light meshes
	auto materialVector = _directionalLightVolume.getMeshMaterialList();
	materialVector.at(0)->setNewMaterialShader("LightPassShader");
	materialVector = _pointLightVolume.getMeshMaterialList();
	materialVector.at(0)->setNewMaterialShader("LightPassShader");
// 	materialVector = _spotLightVolume->getMaterialList();
// 	materialVector.at(0)->setNewMaterialShader("LightPassShader");
}


FScene::~FScene()
{
	_primitiveComponentProxies.clear();
	_lightComponentProxies.clear();
}

void FScene::addPrimitiveComponentProxy(FPrimitiveComponentProxy* toAdd)
{
	//Check that the proxy does not already exists in the scene
	if (!(_primitiveComponentProxies.find(toAdd->getProxyName()) == _primitiveComponentProxies.end()))
	{
		FLog(FLog::ERROR, "PrimitiveComponentProxy already exists in FScene: " + toAdd->getProxyName());
		assert(0);
	}

	_primitiveComponentProxies.insert(std::make_pair(toAdd->getProxyName(), toAdd));
}

void FScene::removePrimitiveComponentProxy(std::string proxyName)
{
	auto it = _primitiveComponentProxies.find(proxyName);

	if (it == _primitiveComponentProxies.end())
	{
		FLog(FLog::ERROR, "PrimitiveComponentProxy doesn't exists in FScene: " + proxyName);
		assert(0);
	}

	_primitiveComponentProxies.erase(it);
}

void FScene::drawAllStaticComponents()
{
	for (auto const &it : _primitiveComponentProxies)
	{
		it.second->drawDynamicElements();
	}
}

void FScene::addLightComponentProxy(FLightComponentProxy* toAdd)
{
	//Check that the proxy does not already exists in the scene
	if (!(_lightComponentProxies.find(toAdd->getProxyName()) == _lightComponentProxies.end()))
	{
		FLog(FLog::ERROR, "LightComponentProxy already exists in FScene: " + toAdd->getProxyName());
		assert(0);
	}

	_lightComponentProxies.insert(std::make_pair(toAdd->getProxyName(), toAdd));
}

void FScene::removeLightComponentProxy(std::string proxyName)
{
	auto it = _lightComponentProxies.find(proxyName);

	if (it == _lightComponentProxies.end())
	{
		FLog(FLog::ERROR, "LightComponentProxy doesn't exists in FScene: " + proxyName);
		assert(0);
	}

	_lightComponentProxies.erase(it);
}

///TODO - Tile based http://gamedev.stackexchange.com/questions/67431/deferred-tiled-shading-tile-frusta-calculation-in-opengl
void FScene::drawAllLightComponents()
{
	//For all the lights render its corresponding mesh and do the light pass.
	for (const auto& it : _lightComponentProxies)
	{
		std::vector<FMaterial*> materialVector;
		switch (it.second->getLightType())
		{
		//Directional light
		case 0:
		{
			//Get the lightVolume material
			materialVector = _directionalLightVolume.getMeshMaterialList();			

			sendLightInformation(it.second, materialVector.front());
			//Render light volume, we use the identity matrix to render a screenQuad
			_directionalLightVolume.renderStaticMesh(Matrix4(1.0));
			break;
		}
		//PointLight
		case 1:
		{
			//Get the lightVolume material
			materialVector = _pointLightVolume.getMeshMaterialList();


			//Check if the player is inside the lightVolume to change the face culling mode
			float distanceToLight = Vector3::length(FEngine::getInstance()->getPlayerController()->getPlayerWorldPosition() - it.second->getLightPosition());
			glEnable(GL_CULL_FACE);
			if (distanceToLight < it.second->getAttenuationRadius())
			{
				glCullFace(GL_FRONT);
			}
			else
			{
				glCullFace(GL_BACK);
			}

			sendLightInformation(it.second, materialVector.front());
			//Render light volume using the new model matrix calculated from the light information
			Matrix4 transformM;
			transformM.translate(it.second->getLightPosition());
			transformM.scale(it.second->getAttenuationRadius());

			_pointLightVolume.renderStaticMesh(transformM);

			glDisable(GL_CULL_FACE);

			break;
		}
		default:
			break;
		}


	}
}

void FScene::sendLightInformation(FLightComponentProxy* light, FMaterial* material)
{
	//Send light information
	material->addUniform_float("Light_Type", light->getLightType());
	material->addUniform_float("Light_Intensity", light->getIntensity());
	material->addUniform_vector3("Light_Color", light->getLightColor());
	material->addUniform_vector3("Light_Position", light->getLightPosition());
	material->addUniform_vector3("Light_Direction", light->getLightDirection());
	material->addUniform_float("Light_AttenuationRadius", light->getAttenuationRadius());

	material->setTextureForTheMaterial("Scene_BaseColor", "DeferredFrameBufferText_Color");
	material->setTextureForTheMaterial("Scene_EmissiveColor", "DeferredFrameBufferText_Emissive");
	material->setTextureForTheMaterial("Scene_Normals", "DeferredFrameBufferText_Normals");
	material->setTextureForTheMaterial("Scene_WorldPosition", "DeferredFrameBufferText_Position");
}
