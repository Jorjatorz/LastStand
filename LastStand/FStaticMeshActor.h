#pragma once

#include <unordered_map>

#include "FActor.h"

//Class that represents an object with a 3D mesh and a material
class FStaticMeshActor : public FActor
{
public:
	FStaticMeshActor(std::string actorName);
	~FStaticMeshActor();

	void setStaticMesh(std::string meshName);
};

