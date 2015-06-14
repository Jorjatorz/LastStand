#pragma once

#include <string>
#include <unordered_map>

class Entity;

//Class that will manage the world. Will contain all the entities, cameras, lights, etc
class FWorld
{
public:
	FWorld();
	~FWorld();

	Entity* addEntityToWorld(std::string name);
	void deleteEntityFromWorld(std::string name);

private:
	std::unordered_map<std::string, Entity*> _entityInWorldList;
};

