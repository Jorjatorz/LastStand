#include "FPrimitiveComponentProxy.h"

#include "FPrimitiveComponent.h"

FPrimitiveComponentProxy::FPrimitiveComponentProxy(FPrimitiveComponent* mTarget)
	:_primitiveComponentPtr(mTarget)
{
}


FPrimitiveComponentProxy::~FPrimitiveComponentProxy()
{//Warning -- Constructor not called when removing need to include it at FPrimitiveComponent
}

std::string FPrimitiveComponentProxy::getProxyName()
{
	return _primitiveComponentPtr->getName();
}
