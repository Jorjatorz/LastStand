#include "FStaticMesh.h"

#include "FResourceManager.h"

FStaticMesh::FStaticMesh()
	:_meshPtr(NULL),
	_materialsList()
{

}

FStaticMesh::FStaticMesh(std::string meshName)
	:_meshPtr(NULL)
{
	//Don't allow empty names
	if (meshName.empty())
	{
		assert(0);
	}

	setNewMesh(meshName);
}

FStaticMesh::~FStaticMesh()
{
}

void FStaticMesh::renderStaticMesh(const Matrix4& worldTransformationM)
{
	_meshPtr->renderAllSubMeshes(worldTransformationM, _materialsList);
}

void FStaticMesh::setNewMesh(std::string meshName)
{
	_meshPtr = FResourceManager::getInstance()->getMeshInMemory(meshName);

	if (!_meshPtr)
	{
		_meshPtr = FResourceManager::getInstance()->loadMeshIntoMemoryFromDisk(meshName);
	}

	_materialsList.resize(_meshPtr->getNumberOfMaterialsSlots());
}

std::vector<FMaterial*> FStaticMesh::getMeshMaterialList()
{
	std::vector<FMaterial*> materialsToRet;
	materialsToRet.reserve(_materialsList.size());
	for (auto& mat : _materialsList)
	{
		materialsToRet.push_back(&mat);
	}

	return materialsToRet;
}