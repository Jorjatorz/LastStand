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
	static_cast<FPrimitiveComponent*>(_componentTarget)->drawDynamicElements();
}
