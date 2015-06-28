#include "FStaticMeshActor.h"

#include "FStaticMeshComponent.h"

FStaticMeshActor::FStaticMeshActor(std::string actorName)
	:FActor(actorName)
{
}

FStaticMeshActor::~FStaticMeshActor()
{
}

void FStaticMeshActor::setStaticMesh(std::string meshName)
{
	//Search for the staticMeshComponent
	auto it = _ownedComponents.cbegin();
	while (it != _ownedComponents.cend())
	{
		FStaticMeshComponent* meshComp = dynamic_cast<FStaticMeshComponent*>(*it);

		//If we are at the static mesh component
		if (meshComp)
		{
			meshComp->setStaticMesh(meshName);
			return;
		}
	}
	//If we have no staticMeshComponent create one
	FStaticMeshComponent* meshComp = addComponentToRootComponent<FStaticMeshComponent>(_name + "_StaticMeshComponent");
	meshComp->setStaticMesh(meshName);
}
