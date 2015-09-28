#include "FLightComponent.h"

#include "FLightComponentProxy.h"
#include "FScene.h"
#include "FRenderer.h"

FLightComponent::FLightComponent(std::string name, FActor* actor)
	:FSceneComponent(name, actor),
	_intensity(1.0),
	_lightColor(1.0),
	_proxyOfComponent(NULL),
	_hasChanged(true)
{

}


FLightComponent::~FLightComponent()
{
}

void FLightComponent::createProxyOfMySelf()
{
	_proxyOfComponent = new FLightComponentProxy(this);
}

void FLightComponent::onAttachedToComponent()
{
	createProxyOfMySelf();

	FRenderer::getInstance()->getCurrentFScene()->addLightComponentProxy(_proxyOfComponent);
}

void FLightComponent::onRemovedFromComponent()
{
	delete _proxyOfComponent;

	FRenderer::getInstance()->getCurrentFScene()->removeLightComponentProxy(_name);
}

void FLightComponent::setLightColor(const Vector3& color)
{
	_lightColor = color;
	_hasChanged = true;
}

void FLightComponent::setIntensity(float newIntensity)
{
	_intensity = newIntensity;
	_hasChanged = true;
}
