#pragma once

#include <string>

//Class that represents an object in the engine.
class FObject
{
public:
	FObject(std::string name);
	~FObject();

	std::string getName()
	{
		return _name;
	}

protected:
	std::string _name;
};

