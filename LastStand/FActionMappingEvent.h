#pragma once

#include "FEvent.h"

#include <set>

class FActionMappingEvent: public FEvent
{
public:
	enum inputEventTypeEnum
	{
		IT_PRESSED,
		IT_RELEASED
	};

	FActionMappingEvent(const std::set<std::string>& actionsTriggered, inputEventTypeEnum typeOfInput, int key);
	~FActionMappingEvent();

	const std::set<std::string>& getActionsTriggered() const
	{
		return *_actionsTriggered;
	}

	inputEventTypeEnum getInputEventType() const
	{
		return _inputEventType;
	}

	int getInputKey() const
	{
		return _inputKey;
	}

private:
	const std::set<std::string>* const _actionsTriggered;
	inputEventTypeEnum _inputEventType;
	int _inputKey;
};

