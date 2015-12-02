#include "FActionMappingEvent.h"

FActionMappingEvent::FActionMappingEvent(const std::set<std::string>& actionsTriggered, inputEventTypeEnum typeOfInput, int key)
	:_actionsTriggered(&actionsTriggered),
	_inputEventType(typeOfInput),
	_inputKey(key)
{
}


FActionMappingEvent::~FActionMappingEvent()
{
}
