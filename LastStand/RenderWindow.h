#pragma once

#include <string>
#include <vector>

//SDL/OPENGL
#include <SDL.h>
#include <gl\glew.h>
#include <gl\gl.h>

#include "SingleInstance.h"

class Viewport;
class FRenderer;
class FWorld;

/*
* Class that is in charge of the rendering window.
* Holds the renderers (Like the world renderer)
*/
class RenderWindow : public SingleInstance<RenderWindow>
{
public:
	RenderWindow(std::string windowName, unsigned short int width, unsigned short int height);
	~RenderWindow();

	//Swaps the back buffer to the fron buffer.
	void swapBuffers(FWorld* currentWorld);

	//Adds a new viewport to the renderWindow. Notice that if two viewports collapse, the last one added will have priority
	Viewport* addViewport(const int& x, const int& y, const int& width, const int& height);

	unsigned short int getWidth()
	{
		return _width;
	}
	unsigned short int getHeight()
	{
		return _height;
	}

private:
	std::string _windowName;
	unsigned short int _width, _height;
	//List of attached viewports
	Viewport* _viewportDisplayed;

	//The renderer of the world
	FRenderer* _worldRenderer;

	//SDL Staff
	SDL_Window* _SDLWindow;
	SDL_GLContext _SDL_GL_Context;
};

