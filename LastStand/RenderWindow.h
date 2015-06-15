#pragma once

#include <string>
#include <vector>

//SDL/OPENGL
#include <SDL.h>
#include <gl\glew.h>
#include <gl\gl.h>

#include "SingleInstance.h"

class Viewport;

/*
* Class that is in charge of the rendering window.
*/
class RenderWindow : public SingleInstance<RenderWindow>
{
public:
	RenderWindow(std::string windowName, unsigned short int width, unsigned short int height);
	~RenderWindow();

	//Swaps the back buffer to the fron buffer.
	void swapBuffers();

	//Adds a new viewport to the renderWindow. Notice that if two viewports collapse, the last one added will have priority
	Viewport* addViewport(const int& x, const int& y, const int& width, const int& height);

private:
	std::string _windowName;
	unsigned short int _width, _height;
	//List of attached viewports
	Viewport* _viewportDisplayed;

	//SDL Staff
	SDL_Window* _SDLWindow;
	SDL_GLContext _SDL_GL_Context;
};

