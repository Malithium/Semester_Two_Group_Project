#define GLEW_STATIC //Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <fstream>

#include <boost/program_options.hpp>

int main(int argc, char *argv[])
{
	//initialise SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	//create SDL Window
	SDL_Window* window = SDL_CreateWindow("OpenGL Window", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

	//create SDL Window context
	SDL_GLContext context = SDL_GL_CreateContext(window);

	if (!window) {
		std::cout << "Failed to create SDL window: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (!context) {
		std::cout << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
		return -1;
	}

	//initialise glew
	 glewInit();
	if (!glewIsSupported("GL_VERSION_3_0")) {
		std::cerr << "OpenGL 3.0 not available" << std::endl;
	return -1;
	}

	//setup SDL windowEvent and game loop
	SDL_Event windowEvent;
	while(true){
		if(SDL_PollEvent(&windowEvent))
		{
			if(windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
		}
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}