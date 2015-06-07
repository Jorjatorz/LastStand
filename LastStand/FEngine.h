#pragma once

#include "Singleton.h"

/*
* Main class of the engine. It initialize and shutdown the engine. Singleton class
*/
class FEngine: public Singleton<FEngine>
{
public:
	FEngine();
	~FEngine();

	void initializeEngine(); //Initialize all the components of the engine.
	void runEngine(); //Starts the main loop of the engine.
};

