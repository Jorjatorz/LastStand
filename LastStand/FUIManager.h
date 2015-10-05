#pragma once

namespace Awesomium
{
	class WebCore;
}

#include <unordered_map>
#include <string>

#include "SingleInstance.h"

class FUIFrame;

//Class that manage the UI objects
class FUIManager: public SingleInstance<FUIManager>
{
public:
	FUIManager();
	~FUIManager();

	//Ticks all the Frames
	void tickFrames(float deltaTime);

	FUIFrame* createUIFrame(std::string frameName);
	void deleteUIFrame(std::string frameName);
	FUIFrame* getUIFrame(std::string frameName);

	//Renders all the UI frames
	void drawAllUIFrames();

private:
	//Awesomium core
	Awesomium::WebCore* _awesomiumWebCore;

	std::unordered_map<std::string, FUIFrame*> _framesMap;
};

