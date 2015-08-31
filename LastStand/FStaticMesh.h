#pragma once

#include "Mesh.h"
#include "FMaterial.h"

#include <string>
#include <vector>

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
	//List with all the materials the mesh posses
	std::vector<FMaterial> _materialsList;
};

