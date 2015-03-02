#define GLEW_STATIC //Easier debugging
#define GLM_FORCE_RADIANS //kill glm errors
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include <boost/program_options.hpp>
#include <src/loadShaders.h>
#include <src/level.h>

int main(int argc, char *argv[])
{

	//initialise SDL
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	
	loadShaders shader;
	Level load;	

	//create SDL Window
	SDL_Window* window = SDL_CreateWindow("OpenGL Window", 100, 100, 1600, 900, SDL_WINDOW_OPENGL);
	
	// " | SDL_WINDOW_FULLSCREEN" Will make it fullscreen - does what the tin says
	
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
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = shader.LoadShaders("shaders/vertex.vs", "shaders/FragmentShader.fragmentshader");


	 // Vertex's for the cube
 	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f
	};

 	// Connects the vertex's to make the cube 
 	static const GLuint element_buffer[] = {
		0, 1, 2,
		2, 3, 0,
		3, 2, 6,
		6, 7, 3,
		7, 6, 5,
		5, 4, 7,
		4, 5, 1,
		1, 0, 4,
		4, 0, 3,
		3, 7, 4,
		1, 5, 6,
		6, 2, 1
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer), element_buffer, GL_STATIC_DRAW);

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");		

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//setup SDL windowEvent and game loop
	SDL_Event windowEvent;
	int lvl = 1; // Will increment per level
	load.runLevel(lvl);
	while (true){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		//MVP code - all this will be inside the camera class, and return an MVP
		glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f); 
		glm::mat4 ViewMatrix = glm::lookAt(
			glm::vec3(4,3,3),
			glm::vec3(0,0,0),
			glm::vec3(0,1,0)
		);
			
		glm::mat4 ModelMatrix = glm::mat4(1.0f);
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

	
		// Draw the triangle !
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

		glDisableVertexAttribArray(0);

		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
		}
		SDL_GL_SwapWindow(window);
	}
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
