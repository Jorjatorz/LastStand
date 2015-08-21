#include "FStaticMeshActor.h"

#include "FStaticMeshComponent.h"

FStaticMeshActor::FStaticMeshActor(std::string actorName)
	:FActor(actorName)
{
	_staticMeshComponentPtr = addComponent<FStaticMeshComponent>("DefaultStaticMeshComponent_" + _name);
}

FStaticMeshActor::~FStaticMeshActor()
{
}

void FStaticMeshActor::setStaticMesh(std::string meshName)
{
	if (_staticMeshComponentPtr)
		_staticMeshComponentPtr->setStaticMesh(meshName);
}

std::vector<FMaterial*> FStaticMeshActor::getMaterialsVector()
{
	if (_staticMeshComponentPtr)
		return _staticMeshComponentPtr->getMeshMaterialsList();

	return std::vector<FMaterial*>();
}