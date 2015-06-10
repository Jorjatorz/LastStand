#pragma once

#include <string>

//SDL/OPENGL
#include <SDL.h>
#include <gl\glew.h>
#include <gl\gl.h>

#include <vector>

class Viewport;

/*
* Class that is in charge of the rendering window.
*/
class RenderWindow
{
public:
	RenderWindow(std::string windowName, unsigned short int width, unsigned short int height);
	~RenderWindow();

	//Swaps the back buffer to the fron buffer.
	void swapBuffers();

	//Adds a new viewport to the renderWindow. Notice that if two viewports collapse, the last one added will have priority
	void addViewport(const int& x, const int& y, const int& width, const int& height);

private:
	std::string _windowName;
	unsigned short int _width, _height;
	//List of attached viewports
	std::vector<Viewport*> _viewportList;

	//SDL Staff
	SDL_Window* mSDLWindow;
	SDL_GLContext mSDL_GL_Context;
};

