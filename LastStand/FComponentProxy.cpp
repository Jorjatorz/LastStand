#include "FComponentProxy.h"

#include "FComponent.h"

FComponentProxy::FComponentProxy(FComponent* proxyTarget)
	:_componentTarget(proxyTarget)
{

}


FComponentProxy::~FComponentProxy()
{
}

std::string FComponentProxy::getProxyName()
{
	return _componentTarget->getName();
}
