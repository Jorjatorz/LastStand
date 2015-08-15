#pragma once

#include <unordered_map>
#include <functional>

#include "FComponent.h"
#include "FActionMappingEvent.h"

//Input components are components that auto registers to the current PlayerController and handles the input events received from this one.
//This input event can be accepted and terminated or accepted and passed to the next input component on the playerController stack (similar to the Chain of Responsibility's pattern)
class FInputComponent: public FComponent
{
public:
	FInputComponent(std::string componentName, FActor* actor);
	~FInputComponent();

	template <class T, class U>
	void bindActionMapping(std::string actionName, FActionMappingEvent::inputEventTypeEnum inputType, T&& functionClass, U&& function)
	{
		_actionMappingsRegistered[actionName] = std::make_pair(std::bind(function, functionClass), inputType);
	}

	template <class T, class U>
	void bindAxisMapping(std::string actionName, T&& functionClass, U&& function)
	{
		_axisMappingzRegistered[actionName] = std::bind(function, functionClass, std::placeholders::_1);
	}

	//Checks if the component accepts the event. Returns true if (after accepting and executing the event) it consumes the event or not.
	bool onActionMappingEventTriggered(const FActionMappingEvent& eventTriggered);
	//Looks for the values in the axis mappings. Called every frame. Returns true if (after accepting and executing the event) it consumes the event or not.
	bool checkAxisMappingsValues();

private:
	std::unordered_map<std::string, std::pair<std::function<void(void)>, FActionMappingEvent::inputEventTypeEnum>> _actionMappingsRegistered;
	std::unordered_map<std::string, std::function<void(float)>> _axisMappingzRegistered;

	//If true the component will consume the event (so it will not be passed to the next inputcompnent)
	bool _terminateEvent;

};

