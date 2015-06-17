#include "FWorld.h"

#include "FLog.h"


FWorld::FWorld()
{
}


FWorld::~FWorld()
{
	for (auto it : _actorsInWorldList)
	{
		delete it.second;
	}
	_actorsInWorldList.clear();
}

void FWorld::removeActortFromWorld(std::string name)
{
	//If doesnt exists
	auto it = _actorsInWorldList.find(name);
	if (it == _actorsInWorldList.end())
	{
		FLog(FLog::ERROR, "Entity doesn't exists in the world, can't delete it: %s", name.c_str());
		assert(0);
	}

	delete it->second;
	_actorsInWorldList.erase(it);
}