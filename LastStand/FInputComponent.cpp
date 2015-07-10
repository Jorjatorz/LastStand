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

void FInputComponent::checkAxisMappingsValues()
{
	FInputManager* manager = FInputManager::getInstance();
	//loop throug all the register axis mappings
	for (const auto& mAxisRegistered : _axisMappingzRegistered)
	{
		float aValue = manager->getAxisValue(mAxisRegistered.first);
		if (aValue != 0.0)
		{
			mAxisRegistered.second(aValue);
		}
	}
}
