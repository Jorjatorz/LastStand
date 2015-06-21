#pragma once

#include "FPrimitiveComponentProxy.h"

class FStaticMeshComponentProxy : public FPrimitiveComponentProxy
{
public:
	FStaticMeshComponentProxy(FPrimitiveComponent* mTarget);
	~FStaticMeshComponentProxy();

	virtual void drawDynamicElements();

};

