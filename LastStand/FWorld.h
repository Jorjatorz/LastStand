#pragma once

#include <string>
#include <unordered_map>

#include "SingleInstance.h"

class FObject;

//Class that will manage the world. Will contain all the entities, cameras, lights, etc
class FWorld : public SingleInstance<FWorld>
{
public:
	FWorld();
	~FWorld();

	template <typename T>
	T* addObjectToWorld(std::string name)
	{
		///Maybe add dynamic_cast to check its a derived class of FObject

		//If already exists
		if (_objectsInWorldList.find(name) != _objectsInWorldList.end())
		{
			FLog(FLog::ERROR, "Object already exists in the world: %s", name.c_str());
			assert(0);
		}

		T* object = new T(name);
		_objectsInWorldList.insert(std::make_pair(name, object));

		return object;
	}
	void removeObjectFromWorld(std::string name);

	//Return a constant pointer to the constant list of objects in world
	const std::unordered_map<std::string, FObject*>* const getObjectsInWorldConstPtr()
	{
		return &_objectsInWorldList;
	}

private:
	std::unordered_map<std::string, FObject*> _objectsInWorldList;
};

