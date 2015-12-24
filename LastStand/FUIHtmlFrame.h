#pragma once

#include "FUIInputFrame.h"

namespace Awesomium
{
	class WebCore;
	class WebView;
}

//UI Input Frame that uses an Html page as texture. Can execute javascripts adn events from the Html page.
class FUIHtmlFrame: public FUIInputFrame
{
public:
	FUIHtmlFrame(std::string frameName);
	~FUIHtmlFrame();

	virtual bool onActionMappingEventTriggered(const FActionMappingEvent& eventTriggered);

	//Changes the html page attached to the frame
	void setHTMLPage(std::string htmlPageName);

private:
	static Awesomium::WebCore* _awesomiumWebCore; //Created with the first html frame, deleted when  _htmlFramesCreated is 0
	static unsigned short int _htmlFramesCreated; //Keeps track of the number of html frames created. When 0, the awesomium web core is deleted.
	Awesomium::WebView* _awesomiumWebView;

	//Creates a texture from the HTML library and set it as the frame texture
	void createAndSetTextureFromWebView();

	virtual void setScale(const Vector3& newScale);

};

