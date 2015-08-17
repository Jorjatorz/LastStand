#pragma once

#include "Mesh.h"

#include <string>

class Matrix4;

//Class that hold a mesh
class FStaticMesh
{
public:
	FStaticMesh();
	FStaticMesh(std::string meshName);
	~FStaticMesh();

	void renderStaticMesh(const Matrix4& worldTransformationM);

	void setNewMesh(std::string meshName);
	std::vector<FMaterial*> getMeshMaterialList();

private:
	Mesh* _meshPtr;
};

