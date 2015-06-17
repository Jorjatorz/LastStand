#pragma once

#include <string>
#include <unordered_map>

#include "SingleInstance.h"

class FActor;

//Class that will manage the world. Will contain all the entities, cameras, lights, etc
class FWorld : public SingleInstance<FWorld>
{
public:
	FWorld();
	~FWorld();

	template <typename T>
	T* addActorToWorld(std::string name)
	{
		///Maybe add dynamic_cast to check its a derived class of FObject

		//If already exists
		if (_actorsInWorldList.find(name) != _actorsInWorldList.end())
		{
			FLog(FLog::ERROR, "Actor already exists in the world: %s", name.c_str());
			assert(0);
		}

		T* object = new T(name);
		_actorsInWorldList.insert(std::make_pair(name, object));

		return object;
	}
	void removeActortFromWorld(std::string name);

	//Return a constant pointer to the constant list of objects in world
	const std::unordered_map<std::string, FActor*>* const getObjectsInWorldConstPtr()
	{
		return &_actorsInWorldList;
	}

private:
	std::unordered_map<std::string, FActor*> _actorsInWorldList;
};

