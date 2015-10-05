#include "FUIManager.h"

#include "FUIFrame.h"
#include "FLog.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

FUIManager::FUIManager()
{
	//Initialize awesomium core
	_awesomiumWebCore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
}


FUIManager::~FUIManager()
{
	//Delete all ui frames
	for (auto& it : _framesMap)
	{
		delete it.second;
	}

	Awesomium::WebCore::Shutdown();
}

FUIFrame* FUIManager::createUIFrame(std::string frameName)
{
	if (_framesMap.find(frameName) != _framesMap.end())
	{
		FLog(FLog::FAILURE, "Can't create the new FUIFrame, it already exists: %s", frameName.c_str());
		assert(0);
		return NULL;
	}
	else
	{
		FUIFrame* newFrame = new FUIFrame(frameName);
		_framesMap.insert(std::make_pair(frameName, newFrame));

		return newFrame;
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
		it.second->tick(deltaTime);
	}
}
