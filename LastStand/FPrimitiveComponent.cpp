#include "FPrimitiveComponent.h"

#include "FRenderer.h"
#include "FScene.h"

FPrimitiveComponent::FPrimitiveComponent(std::string name, FActor* actor)
	:FSceneComponent(name, actor),
	_proxyOfComponent(NULL)
{
}


FPrimitiveComponent::~FPrimitiveComponent()
{
}

void FPrimitiveComponent::onAttachedToComponent()
{
	createProxyOfMySelf();
	//Register in the FScene
	FRenderer::getInstance()->getCurrentFScene()->addPrimitiveComponentProxy(_proxyOfComponent);
}

void FPrimitiveComponent::onRemovedFromComponent()
{
	delete _proxyOfComponent;
	//Remove from FScene
	FRenderer::getInstance()->getCurrentFScene()->removePrimitiveComponentProxy(_name);
}
