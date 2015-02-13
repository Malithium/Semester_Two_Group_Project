#define GLEW_STATIC //Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <fstream>

 // Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <src/shader.hpp>

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

 GLuint VertexArrayID;
 GLuint programID;
 GLuint MatrixID;
 GLuint vertexbuffer;
 GLuint colourbuffer;

 static GLfloat g_colour_buffer_data[12*3*3];  // Colours of ground blocks
 static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};
	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	programID = LoadShaders( "shaders/vertex.vs", "shaders/fragment.fs" );

	// One color for each vertex. They were generated randomly.
	for(int i = 0; i < 1*3; i)
	{ 
		g_colour_buffer_data[3*i0] = 0.140f;
		g_colour_buffer_data[3*i1] = 0.059f;
		g_colour_buffer_data[3*i2] = 0.038f;		
	};

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_colour_buffer_data), g_colour_buffer_data, GL_STATIC_DRAW);

	
	//setup SDL windowEvent and game loop
	SDL_Event windowEvent;
	while(true){
		// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);
	
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : colours
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	
	glDrawArrays(GL_TRIANGLES, 0, 12*3);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
		
		if(SDL_PollEvent(&windowEvent))
		{
			if(windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
		}
		SDL_GL_SwapWindow(window);
	}
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colourbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}