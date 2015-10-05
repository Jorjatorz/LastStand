#include "FPlayerController.h"

#include "FInputManager.h"
#include "FInputComponent.h"
#include "FCameraManager.h"
#include "FEngine.h"
#include "Vector3.h"
#include "FCameraComponent.h"
#include "FUIManager.h"

FPlayerController::FPlayerController()
{
	//Create the camera manager
	_FCameraManagerPtr = new FCameraManager();

	//Create the UI manager
	_FUIManagerPtr = new FUIManager();
}


FPlayerController::~FPlayerController()
{
	//Delete the UI manager
	delete _FUIManagerPtr;

	//Delete the camera manager
	delete _FCameraManagerPtr;
}

void FPlayerController::registerInputComponent(FInputComponent* comp)
{
	_inputComponentsList.push_back(comp);
}

void FPlayerController::unregisterInputComponent(FInputComponent* comp)
{
	auto it = _inputComponentsList.cbegin();
	while (it != _inputComponentsList.cend())
	{
		if (*it == comp)
		{
			_inputComponentsList.erase(it);
			return;
		}
	}
}

void FPlayerController::tick(int deltaTime)
{
	//Check for axis event and communicate to the inputComponents
	std::unordered_map<std::string, float> axisValuesMap = FInputManager::getInstance()->getAxisValuesMap();
	for (const auto& axisIterator : axisValuesMap)
	{
		//If the value is not 0 then communicate to all the input components
		if (axisIterator.second != 0.0f)
		{
			//Start from the end (like a stack). Loop until the end of the list or an inputComp accepts and terminates the event
			auto inputCompIterator = _inputComponentsList.crbegin();
			while ((inputCompIterator != _inputComponentsList.crend()) && (!(*inputCompIterator)->checkAxisMappingsValues(axisIterator.first, axisIterator.second)))
			{
				inputCompIterator++;
			}
		}
	}
	
	//Tick all UIFrames
	_FUIManagerPtr->tickFrames(deltaTime);

	///Update camera target position and rotation so smooth interpolation is achived
}

void FPlayerController::inputEventProduced(const FActionMappingEvent& eventTriggered)
{
	//Start from the end (like a stack). Loop until the end of the list or an inputComp accepts and terminates the event
	auto it = _inputComponentsList.crbegin();
	while ((it != _inputComponentsList.crend()) && (!(*it)->onActionMappingEventTriggered(eventTriggered)))
	{
		it++;
	}
}

void FPlayerController::addYawInput(float degrees)
{
	if (!_pawnPossessed)
	{
		_FCameraManagerPtr->addRotationToViewportCamera(FRotator(0.0, degrees, 0.0));
	}
}

void FPlayerController::addPitchInput(float degrees)
{
	if (!_pawnPossessed)
	{
		_FCameraManagerPtr->addRotationToViewportCamera(FRotator(degrees, 0.0, 0.0));
	}
}

void FPlayerController::addMovementInput(const Vector3& delta)
{
	if (!_pawnPossessed)
	{
		_FCameraManagerPtr->addMovementToViewportCamera(delta * (FEngine::getInstance()->getDeltaTime() / 1000.0f));
	}
}

Vector3 FPlayerController::getPlayerWorldPosition()
{
	if (!_pawnPossessed)
	{
		return _FCameraManagerPtr->getViewportCamera()->getWorldPosition();
	}
}
