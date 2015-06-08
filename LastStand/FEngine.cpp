#include "FEngine.h"

#include "InputManager.h"
#include "RenderWindow.h"

FEngine::FEngine()
	:_engineRunning(true),
	_mainRenderWindowPtr(NULL),
	_inputManagerPtr(NULL)
{
}


FEngine::~FEngine()
{
	delete _inputManagerPtr;
	delete _mainRenderWindowPtr;
}

void FEngine::initializeEngine(std::string windowName, unsigned short int width, unsigned short int height)
{
	//Create the main render window.
	_mainRenderWindowPtr = new RenderWindow(windowName, width, height);
	//Create the Input Manager Singleton
	_inputManagerPtr = new InputManager();
}

void FEngine::runEngine()
{
	//Main game loop
	while (_engineRunning)
	{
		//Poll Hardware input event each frame
		_inputManagerPtr->pollInputEvents();
	}
}

void FEngine::stopEngine()
{
	_engineRunning = false;
}
