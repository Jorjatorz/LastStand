#pragma once

#include "FUIFrame.h"

class FActionMappingEvent;

//Frame that can recive input from the user
class FUIInputFrame: public FUIFrame
{
public:
	FUIInputFrame(std::string frameName);
	~FUIInputFrame();

	virtual bool onActionMappingEventTriggered(const FActionMappingEvent& eventTriggered) = 0;

private:
	//Set the Frametype to private so derived classes cannot change it.
	FUIFrame::_frameType;
};

