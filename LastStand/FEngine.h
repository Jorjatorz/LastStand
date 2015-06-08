#pragma once

#include <memory>
#include <string>

#include "Singleton.h"

//Forward declaration
class RenderWindow;
class InputManager;

/*
* Main class of the engine. It initialize and shutdown the engine. Singleton class
*/
class FEngine: public Singleton<FEngine>
{
public:
	FEngine();
	~FEngine();

	void initializeEngine(std::string windowName, unsigned short int width, unsigned short int height); //Initialize all the components of the engine.
	void runEngine(); //Starts the main loop of the engine.

	//Stop the execution of the mainloop.
	void stopEngine();

private:
	bool _engineRunning;

	//Pointers to Singletons/Unique classes
	RenderWindow* _mainRenderWindowPtr;
	InputManager* _inputManagerPtr;
};

