#include "FInputComponent.h"

#include "FEngine.h"
#include "FWorld.h"
#include "FPlayerController.h"

FInputComponent::FInputComponent(std::string componentName, FActor* actor)
	:FComponent(componentName, actor)
{
	FEngine::getInstance()->getFWorldPtr()->getPlayerController()->registerInputComponent(this);
}


FInputComponent::~FInputComponent()
{
	FEngine::getInstance()->getFWorldPtr()->getPlayerController()->unregisterInputComponent(this);
}

void FInputComponent::tick(float deltaTime)
{
	
}

void FInputComponent::bindActionMapping()
{

}

void FInputComponent::bindAxisMapping()
{

}
