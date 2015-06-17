#pragma once

#include <unordered_map>

#include "FActor.h"

//Class that represents an object with a 3D mesh and a material
class StaticMeshActor : public FActor
{
public:
	StaticMeshActor(std::string name);
	~StaticMeshActor();	
};

