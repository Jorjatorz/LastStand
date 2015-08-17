#include "FStaticMeshComponent.h"

#include "FStaticMeshComponentProxy.h"
#include "Matrix4.h"

FStaticMeshComponent::FStaticMeshComponent(std::string name, FActor* actorParent)
	:FPrimitiveComponent(name, actorParent),
	_staticMesh()
{
}


FStaticMeshComponent::~FStaticMeshComponent()
{
}

void FStaticMeshComponent::drawDynamicElements()
{
	_staticMesh.renderStaticMesh(_worldTransform.getTransformationMatrix());
}

void FStaticMeshComponent::setStaticMesh(std::string meshName)
{
	_staticMesh.setNewMesh(meshName);
}

void FStaticMeshComponent::createProxyOfMySelf()
{
	_proxyOfComponent = new FStaticMeshComponentProxy(this);
}

std::vector<FMaterial*> FStaticMeshComponent::getMeshMaterialsList()
{
	return _staticMesh.getMeshMaterialList();
}