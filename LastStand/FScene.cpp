#include "FScene.h"

#include "FPrimitiveComponentProxy.h"
#include "FLog.h"

FScene::FScene()
{
}


FScene::~FScene()
{
	_primitiveComponentProxies.clear();
}

void FScene::addProxy(FPrimitiveComponentProxy* toAdd)
{
	//Check that the proxy does not already exists in the scene
	if (!(_primitiveComponentProxies.find(toAdd->getProxyName()) == _primitiveComponentProxies.end()))
	{
		FLog(FLog::ERROR, "PrimitiveComponentProxy already exists in FScene: " + toAdd->getProxyName());
		assert(0);
	}

	_primitiveComponentProxies.insert(std::make_pair(toAdd->getProxyName(), toAdd));
}

void FScene::removeProxy(std::string proxyName)
{
	auto it = _primitiveComponentProxies.find(proxyName);

	if (it == _primitiveComponentProxies.end())
	{
		FLog(FLog::ERROR, "PrimitiveComponentProxy doesn't exists in FScene: " + proxyName);
		assert(0);
	}

	_primitiveComponentProxies.erase(it);
}

void FScene::drawAllElements()
{
	for (auto const &it : _primitiveComponentProxies)
	{
		it.second->drawDynamicElements();
	}
}
