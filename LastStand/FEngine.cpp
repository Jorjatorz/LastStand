#include "FEngine.h"

#include "InputManager.h"
#include "RenderWindow.h"
#include "FLog.h"

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
	FLog(FLog::INFO, "Initializing engine components...");

	//Create the main render window.
	_mainRenderWindowPtr = new RenderWindow(windowName, width, height);
	//Create the Input Manager Singleton
	_inputManagerPtr = new InputManager();

	FLog(FLog::INFO, "Engine components initialized");
}

void FEngine::runEngine()
{
	//Main game loop
	while (_engineRunning)
	{
		//Poll Hardware input event each frame
		_inputManagerPtr->pollInputEvents();

		//Swap the buffers
		_mainRenderWindowPtr->swapBuffers();
	}
}

void FEngine::stopEngine()
{
	_engineRunning = false;
}
