#include "FEngine.h"

#include "InputManager.h"
#include "RenderWindow.h"
#include "TimerManager.h"
#include "FLog.h"

FEngine::FEngine()
	:_engineRunning(true),
	_mainRenderWindowPtr(NULL),
	_inputManagerPtr(NULL),
	_timerManagerPtr(NULL)
{
}


FEngine::~FEngine()
{
	delete _timerManagerPtr;
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
	//Create the timer manager
	_timerManagerPtr = new TimerManager();

	FLog(FLog::INFO, "Engine components initialized");
}

void FEngine::runEngine()
{
	//Start the frame timer (this will give the tick to the timermanager
	unsigned int frameStartTime = 0;
	int frames = 0;
	int elapsedTime = 0;

	//Main game loop
	while (_engineRunning)
	{
		//Poll Hardware input event each frame
		_inputManagerPtr->pollInputEvents();

		frameStartTime = _timerManagerPtr->getTotalExecutionTime();

		//Swap the buffers
		_mainRenderWindowPtr->swapBuffers();

		//Frames management
		int deltaTime = _timerManagerPtr->getTotalExecutionTime() - frameStartTime;
		elapsedTime += deltaTime;
		frames++;
		//Update timers
		_timerManagerPtr->tick(deltaTime);

		if (elapsedTime >= 1000)
		{
			FLog(FLog::INFO, "Frames per second: %d", frames);

			elapsedTime = 0;
			frames = 0;
		}
	}
}

void FEngine::stopEngine()
{
	_engineRunning = false;
}
