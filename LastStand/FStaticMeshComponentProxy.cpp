#include "FStaticMeshComponentProxy.h"

#include "FPrimitiveComponent.h"

FStaticMeshComponentProxy::FStaticMeshComponentProxy(FPrimitiveComponent* mTarget)
	:FPrimitiveComponentProxy(mTarget)
{
}


FStaticMeshComponentProxy::~FStaticMeshComponentProxy()
{
}

void FStaticMeshComponentProxy::drawDynamicElements()
{
	_primitiveComponentPtr->drawDynamicElements();
}
