#include "RenderWindow.h"

#include <iostream>

#include "FLog.h"

RenderWindow::RenderWindow(std::string windowName, unsigned short int width, unsigned short int height)
	:_windowName(windowName),
	_width(width),
	_height(height)
{
	FLog(FLog::INFO, "Initializing SDL and GL context. Creating main window");

	//Init SDL and GLEW
	SDL_Init(SDL_INIT_VIDEO);

	//create the window
	mSDLWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL);
	//create the opengl context
	mSDL_GL_Context = SDL_GL_CreateContext(mSDLWindow);

	//Set OPENGL attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(0); //Disable VSync

	glewExperimental = GL_TRUE;
	glewInit();

	//GET INFO
	const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	const char* glslVersion = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::cout << "OpenGL " << version << " initialized." << std::endl;
	std::cout << "(" << vendor << "; " << renderer << ")" << std::endl;
	std::cout << "GLSL version: " << glslVersion << std::endl;
}


RenderWindow::~RenderWindow()
{
	//Delete the context
	SDL_GL_DeleteContext(mSDL_GL_Context);

	//Destroy the window
	SDL_DestroyWindow(mSDLWindow);

	//Stop SDL
	SDL_Quit();
}
