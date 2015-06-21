#pragma once

#include "SingleInstance.h"

#include <unordered_map>

class FPrimitiveComponentProxy;

//Class that represents the scene that is going to be rendered. Contains all the proxies of the PrimitiveComponents to be rendered
class FScene : public SingleInstance<FScene>
{
public:
	FScene();
	~FScene();

	void drawAllElements();

	void addProxy(FPrimitiveComponentProxy* toAdd); //Adds a new proxy. The name of the proxy is given by the component name
	void removeProxy(std::string proxyName); //Remove a proxy from the list (not delete it, thats job of the component itself) given by the proxy name (same as the component name)

private:
	std::unordered_map<std::string, FPrimitiveComponentProxy*> _primitiveComponentProxies;
};

