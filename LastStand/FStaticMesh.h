#pragma once

#include "Mesh.h"

#include <string>

//Class that hold a mesh
class FStaticMesh
{
public:
	FStaticMesh();
	FStaticMesh(std::string meshName);
	~FStaticMesh();

	void renderStaticMesh();

	void setNewMesh(std::string meshName);

private:
	Mesh* _meshPtr;
};

