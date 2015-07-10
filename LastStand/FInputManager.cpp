#include "FInputManager.h"

#include <SDL.h>

#include "FEngine.h"
#include "FWorld.h"
#include "FPlayerController.h"
#include "FActionMappingEvent.h"
#include "Vector3.h"

FInputManager::FInputManager()
	:_mouseX(0.0),
	_mouseY(0.0)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
}


FInputManager::~FInputManager()
{
}

void FInputManager::pollInputEvents()
{
	FPlayerController* pController = FEngine::getInstance()->getFWorldPtr()->getPlayerController();

	//Reset mousemotion values to 0 each frame (so we care if the mouse is not moved)
	handleAxisMappingsForMouseMotion(0.0, 0.0);

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
			_mouseX = mEvent.motion.x;
			_mouseY = mEvent.motion.y;

			handleAxisMappingsForMouseMotion(mEvent.motion.xrel, -mEvent.motion.yrel);
		}

		if (mEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			informAboutInputEventProduced_Pressed(mEvent.button.button, pController);
		}

		if (mEvent.type == SDL_MOUSEBUTTONUP)
		{
			informAboutInputEventProduced_Released(mEvent.button.button, pController);
		}

		if (mEvent.type == SDL_KEYDOWN && mEvent.key.repeat == 0) //Disable key repeats
		{
			informAboutInputEventProduced_Pressed(mEvent.key.keysym.scancode, pController);
		}

		if (mEvent.type == SDL_KEYUP)
		{
			informAboutInputEventProduced_Released(mEvent.key.keysym.scancode, pController);
		}
	}
}

void FInputManager::addActionMapping(std::string actionName, keyTypeEnum keyCode)
{
	auto it = _actionMappingMap.find(keyCode);

	if (it == _actionMappingMap.end())
	{
		std::set<std::string> stringsSet;
		stringsSet.insert(actionName);

		_actionMappingMap.insert(std::make_pair(keyCode, stringsSet));
	}
	else
	{

		std::set<std::string> stringsSet = it->second;
		stringsSet.insert(actionName);

		_actionMappingMap[keyCode] = stringsSet;
	}
}

void FInputManager::addAxisMapping(std::string axisName, keyTypeEnum keyCode, float scale)
{
	auto it = _axisMappingMap.find(keyCode);

	if (it == _axisMappingMap.end())
	{
		std::set<std::string> stringsSet;
		stringsSet.insert(axisName);

		_axisMappingMap.insert(std::make_pair(keyCode, std::make_pair(stringsSet, scale)));
	}
	else
	{

		std::set<std::string> stringsSet = it->second.first;
		stringsSet.insert(axisName);

		_axisMappingMap[keyCode] = std::make_pair(stringsSet, scale);
	}
}

float FInputManager::getAxisValue(std::string axisName)
{
	auto it = _axisMappingCurrentScaleValueMap.find(axisName);

	if (it != _axisMappingCurrentScaleValueMap.end())
	{
		return it->second;
	}

	return 0.0;
}

Vector3 FInputManager::getMousePosition()
{
	return Vector3(_mouseX, _mouseY, 0.0);
}

void FInputManager::informAboutInputEventProduced_Pressed(int key, FPlayerController* currentController)
{
	//Action mappings
	auto bindingsActions = _actionMappingMap.find(key);
	if ((bindingsActions != _actionMappingMap.end() && (!bindingsActions->second.empty())))
	{
		//Create the event
		FActionMappingEvent actionEvent(_actionMappingMap.find(key)->second, FActionMappingEvent::IT_PRESSED);
		//Send the event
		currentController->inputEventProduced(actionEvent);
	}

	//Axis mappings
	auto bindingsAxis = _axisMappingMap.find(key);
	if ((bindingsAxis != _axisMappingMap.end() && (!bindingsAxis->second.first.empty())))
	{
		//Set all the current axis value of the mappings of that key to its corresponding value
		for (const auto& it : bindingsAxis->second.first)
		{
			_axisMappingCurrentScaleValueMap[it] = bindingsAxis->second.second;
		}
	}
}

void FInputManager::informAboutInputEventProduced_Released(int key, FPlayerController* currentController)
{
	//Action mappings
	auto bindings = _actionMappingMap.find(key);
	if ((bindings != _actionMappingMap.end() && (!bindings->second.empty())))
	{
		//Create the event
		FActionMappingEvent actionEvent(_actionMappingMap.find(key)->second, FActionMappingEvent::IT_RELEASED);
		//Send the event
		currentController->inputEventProduced(actionEvent);
	}

	//Axis mappings
	auto bindingsAxis = _axisMappingMap.find(key);
	if ((bindingsAxis != _axisMappingMap.end() && (!bindingsAxis->second.first.empty())))
	{
		//Set all the current axis value of the mappings of that key to 0
		for (const auto& it : bindingsAxis->second.first)
		{
			_axisMappingCurrentScaleValueMap[it] = 0.0f;
		}
	}
}

void FInputManager::handleAxisMappingsForMouseMotion(int relativeMovementX, int relativeMovementY)
{
	//Axis mappings for MOUSE_X
	auto bindingsAxis = _axisMappingMap.find(MOUSE_X);
	if ((bindingsAxis != _axisMappingMap.end() && (!bindingsAxis->second.first.empty())))
	{
		//Set all the current axis value of the mappings of that key to its corresponding value
		for (const auto& it : bindingsAxis->second.first)
		{
			_axisMappingCurrentScaleValueMap[it] = bindingsAxis->second.second * relativeMovementX;
		}
	}

	//Axis mappings for MOUSE_Y
	bindingsAxis = _axisMappingMap.find(MOUSE_Y);
	if ((bindingsAxis != _axisMappingMap.end() && (!bindingsAxis->second.first.empty())))
	{
		//Set all the current axis value of the mappings of that key to its corresponding value
		for (const auto& it : bindingsAxis->second.first)
		{
			_axisMappingCurrentScaleValueMap[it] = bindingsAxis->second.second * relativeMovementY;
		}
	}
}
