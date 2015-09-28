#include "FWorld.h"

#include "FLog.h"
#include "FActor.h"

FWorld::FWorld()
{
}


FWorld::~FWorld()
{
	for (auto &it : _actorsInWorldList)
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

void FWorld::tick(int deltaTime)
{
	//Tick player controller
	_playerWorldController.tick(deltaTime);
	//Tick all the actors in world
	for (auto const &actor : _actorsInWorldList)
	{
		if (actor.second->canTick())
		{
			actor.second->tickActor(deltaTime);
		}
	}
}
