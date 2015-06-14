#include "FWorld.h"

#include "FLog.h"
#include "Entity.h"

FWorld::FWorld()
{
}


FWorld::~FWorld()
{
	for (auto it : _entityInWorldList)
	{
		delete it.second;
	}
	_entityInWorldList.clear();
}

Entity* FWorld::addEntityToWorld(std::string name)
{
	//If already exists
	if (_entityInWorldList.find(name) != _entityInWorldList.end())
	{
		FLog(FLog::ERROR, "Entity already exists in the world: %s", name.c_str());
		assert(0);
	}

	Entity* ent = new Entity(name);
	_entityInWorldList.insert(std::make_pair(name, ent));

	return ent;
}

void FWorld::deleteEntityFromWorld(std::string name)
{
	//If doesnt exists
	auto it = _entityInWorldList.find(name);
	if (it == _entityInWorldList.end())
	{
		FLog(FLog::ERROR, "Entity doesn't exists in the world, can't delete it: %s", name.c_str());
		assert(0);
	}

	delete it->second;
	_entityInWorldList.erase(it);
}
