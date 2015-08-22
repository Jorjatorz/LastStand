#include "FInputComponent.h"

#include "FEngine.h"
#include "FWorld.h"
#include "FPlayerController.h"
#include "FInputManager.h"

FInputComponent::FInputComponent(std::string componentName, FActor* actor)
	:FComponent(componentName, actor),
	_terminateEvent(true)
{
	FEngine::getInstance()->getFWorldPtr()->getPlayerController()->registerInputComponent(this);
}


FInputComponent::~FInputComponent()
{
	FEngine::getInstance()->getFWorldPtr()->getPlayerController()->unregisterInputComponent(this);
}

bool FInputComponent::onActionMappingEventTriggered(const FActionMappingEvent& eventTriggered)
{
	//loop through all the action mappings
	for (const auto& actionTriggered : eventTriggered.getActionsTriggered())
	{
		for (const auto& mActionsRegistered : _actionMappingsRegistered)
		{
			//Check if this action is the one we are looking for
			if (mActionsRegistered.first == actionTriggered)
			{
				//Check if the type of input is the desired
				if (mActionsRegistered.second.second == eventTriggered.getInputEventType())
				{
					//Execute the action
					mActionsRegistered.second.first();

					//Return
					return _terminateEvent;
				}
			}
		}
	}

	//Dont consume the event as we didnt find it
	return false;
}

bool FInputComponent::checkAxisMappingsValues()
{
	FInputManager* manager = FInputManager::getInstance();

	bool eventConsumed = false;
	//Loop through all the registered axis mappings in this component and if the axisValue is different from 0 execute the action.
	for (const auto& mAxisRegistered : _axisMappingzRegistered)
	{
		float aValue = manager->getAxisValue(mAxisRegistered.first);
		if (aValue != 0.0)
		{
			mAxisRegistered.second(aValue);

			eventConsumed = true;
		}
	}

	//If any axisMapping is consumed we return _terminateEvent.
	if (eventConsumed)
	{
		return _terminateEvent;
	}
	else
	{
		//No axis input was triggered, so we dont terminate the event (return false)
		return false;
	}
}

void FInputComponent::setPropagateEvent(bool propagate)
{
	_terminateEvent = !propagate;
}
