#pragma once

#include "FActor.h"

class FMaterial;

//Class that represents an object with a 3D mesh and a material
class FStaticMeshActor : public FActor
{
public:
	FStaticMeshActor(std::string actorName);
	~FStaticMeshActor();

	//Sets the static mesh to the staticMeshComponent. If the component doesnt exists it creates one.
	void setStaticMesh(std::string meshName);

	///Facil para debugear. Borrar 
	std::vector<FMaterial*> getMaterialsVector();
};

