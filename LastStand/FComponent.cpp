#include "FComponent.h"

#include "FActor.h"

FComponent::FComponent(std::string name, FActor* actorP)
	:FObject(name),
	_parentActor(actorP)
{
	_parentActor->addOwnedComponent(this);
}


FComponent::~FComponent()
{
	_parentActor->removeOwnedComponent(this);
}

void FComponent::setParent(FActor* newParent)
{
	_parentActor = newParent;
}
