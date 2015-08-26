#include "FDirectionalLightComponent.h"

#include "FLightComponentProxy.h"
#include "FScene.h"
#include "FRenderer.h"

FDirectionalLightComponent::FDirectionalLightComponent(std::string name, FActor* actor)
	:FLightComponent(name, actor)
{

}


FDirectionalLightComponent::~FDirectionalLightComponent()
{
}

void FDirectionalLightComponent::createProxyOfMySelf()
{
	_proxyOfComponent = new FLightComponentProxy(this);
}

void FDirectionalLightComponent::onAttachedToComponent()
{
	createProxyOfMySelf();

	FRenderer::getInstance()->getCurrentFScene()->addLightComponentProxy(_proxyOfComponent);
}

void FDirectionalLightComponent::onRemovedFromComponent()
{
	delete _proxyOfComponent;

	FRenderer::getInstance()->getCurrentFScene()->removeLightComponentProxy(_name);
}

FLightComponent::lightTypeEnum FDirectionalLightComponent::getLightType()
{
	return FLightComponent::DIRECTIONALLIGHT;
}
