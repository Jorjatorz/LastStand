#pragma once

namespace Awesomium
{
	class WebCore;
}

#include <unordered_map>
#include <string>

#include "SingleInstance.h"

class FUIFrame;
class FActionMappingEvent;

//Class that manage the UI objects
class FUIManager: public SingleInstance<FUIManager>
{
public:
	FUIManager();
	~FUIManager();

	//Ticks all the Frames
	void tickFrames(float deltaTime);

	template <typename T>
	T* createUIFrame(std::string frameName)
	{
		if (_framesMap.find(frameName) != _framesMap.end())
		{
			FLog(FLog::FAILURE, "Can't create the new FUIFrame, it already exists: %s", frameName.c_str());
			assert(0);
			return NULL;
		}
		else
		{
			T* newFrame = new T(frameName);
			_framesMap.insert(std::make_pair(frameName, newFrame));

			return newFrame;
		}
	}

	void deleteUIFrame(std::string frameName);
	FUIFrame* getUIFrame(std::string frameName);

	//Renders all the UI frames
	void drawAllUIFrames();

	//Handles action mapping events. Return true if the event was handled by any UIFrame
	bool onActionMappingEventTriggered(const FActionMappingEvent& eventTriggered);
private:
	//Awesomium core
	Awesomium::WebCore* _awesomiumWebCore;

	std::unordered_map<std::string, FUIFrame*> _framesMap;
};

