#pragma once

#include "FPrimitiveComponent.h"
#include "FStaticMesh.h"

#include <string>

//Component that holds a static mesh (and renders it)
class FStaticMeshComponent : public FPrimitiveComponent
{
public:
	FStaticMeshComponent(std::string name, FActor* actorParent);
	~FStaticMeshComponent();

	virtual void drawDynamicElements();

	void setStaticMesh(std::string meshName);
	//Return a vector with all the elements of the mesh
	std::vector<FMaterial*> getMeshMaterialsList();

protected:
	virtual void createProxyOfMySelf();

private:
	FStaticMesh _staticMesh;
};

