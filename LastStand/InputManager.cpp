#include "InputManager.h"

#include <SDL.h>

#include "FEngine.h"

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::pollInputEvents()
{
	SDL_Event mEvent;

	while (SDL_PollEvent(&mEvent))
	{
		if (mEvent.type == SDL_QUIT)
		{
			FEngine::getInstance()->stopEngine();
			break;
		}

		if (mEvent.type == SDL_MOUSEMOTION)
		{
			
		}

		if (mEvent.type == SDL_MOUSEBUTTONDOWN)
		{

		}

		if (mEvent.type == SDL_MOUSEBUTTONUP)
		{
		
		}

		if (mEvent.type == SDL_KEYDOWN)
		{
			
		}

		if (mEvent.type == SDL_KEYUP)
		{
			
		}
	}
}
