#include "FStaticMesh.h"

#include "FEngine.h"
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

	_meshPtr = FEngine::getSingleton()->getResourceManagerPtr()->getMeshInMemory(meshName);

	if (!_meshPtr)
	{
		_meshPtr = FEngine::getSingleton()->getResourceManagerPtr()->loadMeshIntoMemoryFromDisk(meshName);
	}
}

FStaticMesh::~FStaticMesh()
{
}

void FStaticMesh::renderStaticMesh()
{
	_meshPtr->renderAllSubMeshes();
}

void FStaticMesh::setNewMesh(std::string meshName)
{
	_meshPtr = FEngine::getSingleton()->getResourceManagerPtr()->getMeshInMemory(meshName);

	if (!_meshPtr)
	{
		_meshPtr = FEngine::getSingleton()->getResourceManagerPtr()->loadMeshIntoMemoryFromDisk(meshName);
	}
}
