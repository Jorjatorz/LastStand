#pragma once

#include <iostream>
#include <string>

//SDL/OPENGL
#include <SDL.h>
#include <gl\glew.h>
#include <gl\gl.h>

/*
* Class that is in charge of the rendering window.
*/
class RenderWindow
{
public:
	RenderWindow(std::string windowName, unsigned short int width, unsigned short int height);
	~RenderWindow();

private:
	std::string _windowName;
	unsigned short int _width, _height;

	//SDL Staff
	SDL_Window* mSDLWindow;
	SDL_GLContext mSDL_GL_Context;
};

