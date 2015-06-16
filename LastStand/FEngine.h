#pragma once

#include <string>

#include "Singleton.h"

//Forward declaration
class FResourceManager;
class InputManager;
class RenderWindow;
class TimerManager;
class FWorld;


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

	//Return a pointer to the main rendering window
	RenderWindow* const getRenderWindowPtr()
	{
		return _mainRenderWindowPtr;
	}
	//Fast and global acces for some rendering window properties
	unsigned short int getRenderingWindow_Width();
	unsigned short int getRenderingWindow_Height();

	//Retun a pointer to the timer manager
	TimerManager* const getTimerManagePtr()
	{
		return _timerManagerPtr;
	}
	//Return a pointer to the resource manager
	FResourceManager* const getResourceManagerPtr()
	{
		return _FResourceManagerPtr;
	}
	//Return a pointer to the current world
	FWorld* const getFWorldPtr()
	{
		return _FWorldPtr;
	}

private:
	bool _engineRunning;

	//Pointers to Singletons/Unique classes
	RenderWindow* _mainRenderWindowPtr;
	InputManager* _inputManagerPtr;
	TimerManager* _timerManagerPtr;
	FResourceManager* _FResourceManagerPtr;
	FWorld* _FWorldPtr;
};

