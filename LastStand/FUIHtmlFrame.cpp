#include "FUIHtmlFrame.h"

#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>

#include "FEngine.h"
#include "FResourceManager.h"
#include "Texture.h"

Awesomium::WebCore* FUIHtmlFrame::_awesomiumWebCore = 0;
unsigned short int FUIHtmlFrame::_htmlFramesCreated = 0;

FUIHtmlFrame::FUIHtmlFrame(std::string frameName)
	:FUIInputFrame(frameName)
{
	_htmlFramesCreated++;
	if (_htmlFramesCreated == 1)
	{
		_awesomiumWebCore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
	}

	_awesomiumWebView = _awesomiumWebCore->CreateWebView(FEngine::getInstance()->getRenderingWindow_Width() * _scale.x, FEngine::getInstance()->getRenderingWindow_Height() * _scale.y);
}


FUIHtmlFrame::~FUIHtmlFrame()
{
	_awesomiumWebView->Destroy();

	_htmlFramesCreated--;

	if (_htmlFramesCreated == 0)
	{
		Awesomium::WebCore::Shutdown();
	}
}

bool FUIHtmlFrame::onActionMappingEventTriggered(const FActionMappingEvent& eventTriggered)
{
	return false;
}

void FUIHtmlFrame::setHTMLPage(std::string htmlPageName)
{
	_awesomiumWebView->LoadURL(Awesomium::WebURL(Awesomium::WSLit(htmlPageName.c_str())));

	while (_awesomiumWebView->IsLoading())
	{
		_awesomiumWebCore->Update();
	}

	Sleep(5); //Sleep a bit to enable awesomium update everything
	_awesomiumWebCore->Update();

	createAndSetTextureFromWebView();
}

void FUIHtmlFrame::createAndSetTextureFromWebView()
{
	Awesomium::BitmapSurface* surface = (Awesomium::BitmapSurface*)_awesomiumWebView->surface();
	if (surface)
	{
		unsigned char* buff = new unsigned char[surface->width() * surface->height() * 4];
		surface->CopyTo(buff, surface->row_span(), 4, true, true);

		if (!_frameTexture)
		{
			
			Texture* uiText = FResourceManager::getInstance()->createNewTextureInMemory(_name + "HTML_Texture", surface->width(), surface->height(), GL_RGBA, false, buff);
			setTexture(uiText);
		}
		else
		{
			_frameTexture->updateTexture(surface->width(), surface->height(), GL_RGBA, false, buff);
		}

		delete[] buff;
	}
}

void FUIHtmlFrame::setScale(const Vector3& newScale)
{
	FUIFrame::setScale(newScale);

	_awesomiumWebView->Resize(FEngine::getInstance()->getRenderingWindow_Width() * _scale.x, FEngine::getInstance()->getRenderingWindow_Height() * _scale.y);
	Sleep(5); //Sleep a bit to enable awesomium update everything
	_awesomiumWebCore->Update();

	createAndSetTextureFromWebView();
}
