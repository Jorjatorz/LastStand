#include "FPlayerController.h"

#include "FInputComponent.h"
#include "FCameraManager.h"

FPlayerController::FPlayerController()
{
	//Create the camera manager
	_FCameraManagerPtr = new FCameraManager();
}


FPlayerController::~FPlayerController()
{
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
	//Each tick check for axis mapping
	//Start from the end
	auto it = _inputComponentsList.crbegin();
	while ((it != _inputComponentsList.crend()))
	{
		(*it)->checkAxisMappingsValues();
		it++;
	}

	//Update camera each frame from the camera controller
}

void FPlayerController::inputEventProduced(const FActionMappingEvent& eventTriggered)
{
	//Start from the end
	auto it = _inputComponentsList.crbegin();

	while ((it != _inputComponentsList.crend()) && (!(*it)->onActionMappingEventTriggered(eventTriggered)))
	{
		it++;
	}
}

void FPlayerController::addYawInput(float degrees)
{
	_FCameraManagerPtr->addRotationToViewportCamera(FRotator(0.0, degrees, 0.0));
}

void FPlayerController::addPitchInput(float degrees)
{
	_FCameraManagerPtr->addRotationToViewportCamera(FRotator(degrees, 0.0, 0.0));
}