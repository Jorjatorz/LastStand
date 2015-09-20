#pragma once

#include "SingleInstance.h"
#include "FStaticMesh.h"

#include <unordered_map>

class FPrimitiveComponentProxy;
class FLightComponentProxy;
class FMaterial;

//Class that represents the scene that is going to be rendered. Contains all the proxies of the PrimitiveComponents to be rendered
class FScene : public SingleInstance<FScene>
{
public:
	FScene();
	~FScene();

	//Renders all the meshes of the staticCompoenntsProxies
	void drawAllStaticComponents();
	//Renders all the lights and their corresponding lightMesh
	void drawAllLightComponents();

	//Adds a new primitiveComponentProxy. The name of the proxy is given by the component name
	void addPrimitiveComponentProxy(FPrimitiveComponentProxy* toAdd);
	//Remove a primitiveComponentProxy from the list (not delete it, thats job of the component itself) given the proxy name (same as the component name)
	void removePrimitiveComponentProxy(std::string proxyName); 

	//Adds a new lightComponentProxy. The name of the proxy is given by the component name
	void addLightComponentProxy(FLightComponentProxy* toAdd);
	//Remove a lightComponentProxy from the list (not delete it, thats job of the component itself) given the proxy name (same as the component name)
	void removeLightComponentProxy(std::string proxyName);

private:
	//Map with the primitiveComponentProxies
	std::unordered_map<std::string, FPrimitiveComponentProxy*> _primitiveComponentProxies;
	//Map with the lightComponentsProxies
	std::unordered_map<std::string, FLightComponentProxy*> _lightComponentProxies;

	//Light Volumes
	FStaticMesh _directionalLightVolume;
	FStaticMesh _pointLightVolume;
	FStaticMesh _spotLightVolume;
	//Sends the light information to the material
	void sendLightInformation(FLightComponentProxy* light, FMaterial* material);
};

