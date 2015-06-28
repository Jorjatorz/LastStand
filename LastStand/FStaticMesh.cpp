#include "FStaticMesh.h"

#include "FResourceManager.h"

FStaticMesh::FStaticMesh()
	:_meshPtr(NULL)
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

	_meshPtr = FResourceManager::getInstance()->getMeshInMemory(meshName);

	if (!_meshPtr)
	{
		_meshPtr = FResourceManager::getInstance()->loadMeshIntoMemoryFromDisk(meshName);
	}
}

FStaticMesh::~FStaticMesh()
{
}

void FStaticMesh::renderStaticMesh(const Matrix4& worldTransformationM)
{
	_meshPtr->renderAllSubMeshes(worldTransformationM);
}

void FStaticMesh::setNewMesh(std::string meshName)
{
	_meshPtr = FResourceManager::getInstance()->getMeshInMemory(meshName);

	if (!_meshPtr)
	{
		_meshPtr = FResourceManager::getInstance()->loadMeshIntoMemoryFromDisk(meshName);
	}
}
