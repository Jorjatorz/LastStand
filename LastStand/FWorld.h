#pragma once

#include <string>
#include <unordered_map>

#include "SingleInstance.h"
#include "FPlayerController.h"

class FActor;

//Class that will manage the world. Will contain all the entities, cameras, lights, etc
class FWorld : public SingleInstance<FWorld>
{
public:
	FWorld();
	~FWorld();

	void tick(int deltaTime);

	template <typename T>
	T* addActorToWorld(std::string name)
	{
		///Maybe add dynamic_cast to check its a derived class of FObject

		//If already exists
		if (_actorsInWorldList.find(name) != _actorsInWorldList.end())
		{
			FLog(FLog::FAILURE, "Actor already exists in the world: %s", name.c_str());
			assert(0);
		}

		T* object = new T(name);
		_actorsInWorldList.insert(std::make_pair(name, object));

		return object;
	}
	void removeActortFromWorld(std::string name);

	FPlayerController* const getPlayerController()
	{
		return &_playerWorldController;
	}

private:
	std::unordered_map<std::string, FActor*> _actorsInWorldList;
	//World human player controller
	FPlayerController _playerWorldController;
};

