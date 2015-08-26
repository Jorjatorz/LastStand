#include "FPrimitiveComponentProxy.h"

#include "FPrimitiveComponent.h"

FPrimitiveComponentProxy::FPrimitiveComponentProxy(FPrimitiveComponent* mTarget)
	:FComponentProxy(mTarget)
{
}


FPrimitiveComponentProxy::~FPrimitiveComponentProxy()
{//Warning -- Constructor not called when removing need to include it at FPrimitiveComponent
}