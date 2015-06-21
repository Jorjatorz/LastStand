#include "FPrimitiveComponentProxy.h"

#include "FPrimitiveComponent.h"

FPrimitiveComponentProxy::FPrimitiveComponentProxy(FPrimitiveComponent* mTarget)
	:_primitiveComponentPtr(mTarget)
{
}


FPrimitiveComponentProxy::~FPrimitiveComponentProxy()
{
}

std::string FPrimitiveComponentProxy::getProxyName()
{
	return _primitiveComponentPtr->getName();
}
