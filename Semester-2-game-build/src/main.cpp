#define GLEW_STATIC //Easier debugging
#define GLM_FORCE_RADIANS //kill glm errors
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream> 

#include <boost/program_options.hpp>
#include <src/level.h>

using namespace std;

/**
* The main method creates our SDL window, and begins our game loop, before then proceeding into the level loop
*/
int main(int argc, char *argv[])
{
	//initialise SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	
	Level load;
	int lvl = 1; // Will increment every level		

	//create SDL Window
	SDL_Window* window = SDL_CreateWindow("Cube Jumper", 100, 100, 1200, 800, SDL_WINDOW_OPENGL);

	// | SDL_WINDOW_FULLSCREEN_DESKTOP	

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

	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	while (true){
		if(load.runLevel(lvl, window) == true)
		{
			lvl++;
		}
		else
		{
			break;
		}

	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
