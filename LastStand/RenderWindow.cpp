#include "RenderWindow.h"

#include <iostream>

#include "FWorldRenderer.h"
#include "FLog.h"
#include "Viewport.h"

RenderWindow::RenderWindow(std::string windowName, unsigned short int width, unsigned short int height)
	:_windowName(windowName),
	_width(width),
	_height(height),
	_viewportDisplayed(NULL)
{
	FLog(FLog::INFO, "Initializing SDL and GL context. Creating main window");

	//Init SDL and GLEW
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		FLog(FLog::ERROR, "Unable to initialize SDL");
	}

	//create the window
	_SDLWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL);
	//create the opengl context
	_SDL_GL_Context = SDL_GL_CreateContext(_SDLWindow);

	// Set OPENGL attributes
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

	//Create the world renderer
	_worldRenderer = new FWorldRenderer(_width, _height);
}


RenderWindow::~RenderWindow()
{
	//Delete the viewport
	if (_viewportDisplayed)
	{
		delete _viewportDisplayed;
	}

	delete _worldRenderer;

	//Delete the context
	SDL_GL_DeleteContext(_SDL_GL_Context);

	//Destroy the window
	SDL_DestroyWindow(_SDLWindow);

	//Stop SDL
	SDL_Quit();
}

Viewport* RenderWindow::addViewport(const int& x, const int& y, const int& width, const int& height)
{
	//If the viewport already exists delete it
	if (_viewportDisplayed)
	{
		delete _viewportDisplayed;
	}
	_viewportDisplayed = new Viewport(x, y, width, height);

	return _viewportDisplayed;
}

void RenderWindow::swapBuffers(FWorld* currentWorld)
{
	//Gl enables
	//glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);

	//Clear the buffer each frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (_viewportDisplayed)
	{
		_viewportDisplayed->updateViewport();
	}

	_worldRenderer->renderObjectsInTheWorld(currentWorld, _viewportDisplayed->getViewportViewMatrix());

	SDL_GL_SwapWindow(_SDLWindow);
}
