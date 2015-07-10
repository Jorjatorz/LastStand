#include "FActionMappingEvent.h"

FActionMappingEvent::FActionMappingEvent(const std::set<std::string>& actionsTriggered, inputEventTypeEnum typeOfInput)
	:_actionsTriggered(&actionsTriggered),
	_inputEventType(typeOfInput)
{
}


FActionMappingEvent::~FActionMappingEvent()
{
}
