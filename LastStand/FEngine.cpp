#include "FEngine.h"

#include "FResourceManager.h"
#include "FInputManager.h"
#include "RenderWindow.h"
#include "TimerManager.h"
#include "FLog.h"
#include "FWorld.h"
#include "FPlayerController.h"

FEngine::FEngine()
	:_engineRunning(true),
	_mainRenderWindowPtr(NULL),
	_inputManagerPtr(NULL),
	_timerManagerPtr(NULL),
	_FResourceManagerPtr(NULL)
{
}


FEngine::~FEngine()
{
	delete _inputManagerPtr;
	delete _mainRenderWindowPtr;
	delete _FWorldPtr;
	delete _timerManagerPtr;
	delete _FResourceManagerPtr;
}

void FEngine::initializeEngine(std::string windowName, unsigned short int width, unsigned short int height)
{
	FLog(FLog::INFO, "Initializing engine components...");

	//Create the resource manager
	_FResourceManagerPtr = new FResourceManager();
	//Create the timer manager
	_timerManagerPtr = new TimerManager();
	//Create the world manager
	_FWorldPtr = new FWorld();
	//Create the main render window.
	_mainRenderWindowPtr = new RenderWindow(windowName, width, height);
	//Create the Input Manager Singleton
	_inputManagerPtr = new FInputManager();

	FLog(FLog::INFO, "Engine components initialized");
}

void FEngine::runEngine()
{
	//Start the frame timer (this will give the tick to the timermanager
	unsigned int frameStartTime = 0;
	int frames = 0;
	int elapsedTime = 0;
	int deltaTime = 0;

	//Main game loop
	while (_engineRunning)
	{
		//Poll Hardware input event each frame
		_inputManagerPtr->pollInputEvents();

		frameStartTime = _timerManagerPtr->getTotalExecutionTime();

		//Update timers
		_timerManagerPtr->tick(deltaTime);
		//Tick the world. This will tick all the Actors and components if activated
		_FWorldPtr->tick(deltaTime);

		//Render the world and Swap the buffers
		_mainRenderWindowPtr->swapBuffers();

		//Frames management
		deltaTime = _timerManagerPtr->getTotalExecutionTime() - frameStartTime;
		if (deltaTime < 1000 / 60.0f)
		{
			SDL_Delay(1000 / 60.0f - deltaTime);

			deltaTime = 1000 / 60.0f;
		}

		elapsedTime += deltaTime;
		frames++;

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

unsigned short int FEngine::getRenderingWindow_Width()
{
	return _mainRenderWindowPtr->getWidth();
}

unsigned short int FEngine::getRenderingWindow_Height()
{
	return _mainRenderWindowPtr->getHeight();
}

int FEngine::getDeltaTime()
{
	return _timerManagerPtr->getDeltaTime();
}

FPlayerController* const FEngine::getPlayerController() const
{
		return _FWorldPtr->getPlayerController();
}
