#include "FWorld.h"

#include "FLog.h"


FWorld::FWorld()
{
}


FWorld::~FWorld()
{
	for (auto it : _objectsInWorldList)
	{
		delete it.second;
	}
	_objectsInWorldList.clear();
}

void FWorld::removeObjectFromWorld(std::string name)
{
	//If doesnt exists
	auto it = _objectsInWorldList.find(name);
	if (it == _objectsInWorldList.end())
	{
		FLog(FLog::ERROR, "Entity doesn't exists in the world, can't delete it: %s", name.c_str());
		assert(0);
	}

	delete it->second;
	_objectsInWorldList.erase(it);
}