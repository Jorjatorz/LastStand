#include "FUIManager.h"

#include "FUIFrame.h"
#include "FUIInputFrame.h"
#include "FLog.h"
#include "FActionMappingEvent.h"

FUIManager::FUIManager()
{
}


FUIManager::~FUIManager()
{
	//Delete all ui frames
	for (auto& it : _framesMap)
	{
		delete it.second;
	}
}

void FUIManager::deleteUIFrame(std::string frameName)
{
	auto it = _framesMap.find(frameName);
	if (it == _framesMap.end())
	{
		FLog(FLog::FAILURE, "Can't delete the FUIFrame, it doesn't exists: %s", frameName.c_str());
		assert(0);
	}
	else
	{
		delete it->second;
		_framesMap.erase(it);
	}
}

FUIFrame* FUIManager::getUIFrame(std::string frameName)
{
	auto it = _framesMap.find(frameName);
	if (it != _framesMap.end())
	{
		return it->second;
	}
	else
	{
		FLog(FLog::WARNING, "Can't return the FUIFrame, it doesn't exists: %s", frameName.c_str());
		return NULL;
	}
}

void FUIManager::drawAllUIFrames()
{
	for (const auto& it : _framesMap)
	{
		it.second->renderFrame();
	}
}

void FUIManager::tickFrames(float deltaTime)
{
	for (const auto& it : _framesMap)
	{
		it.second->tickFrame(deltaTime);
	}
}

bool FUIManager::onActionMappingEventTriggered(const FActionMappingEvent& eventTriggered)
{
	for (const auto& frame : _framesMap)
	{
		if (frame.second->getType() == FUIInputFrame::INPUT_FRAME)
		{
			bool consumed = static_cast<FUIInputFrame*>(frame.second)->onActionMappingEventTriggered(eventTriggered);
		}
	}

	return false;
}
