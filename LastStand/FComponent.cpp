#include "FComponent.h"

#include "FActor.h"

FComponent::FComponent(std::string name, FActor* actorP)
	:FObject(name),
	_ownerActor(actorP)
{
	_ownerActor->addOwnedComponent(this);
}


FComponent::~FComponent()
{
	_ownerActor->removeOwnedComponent(this);
}

void FComponent::setOwner(FActor* newOwner)
{
	_ownerActor = newOwner;
}
