
#include <cube.h>

//This will be overwritten by individual cube sizes
void size()
{
 GLfloat g_vertex_buffer_data[] = { 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
 GLuint element_buffer[] = { 0, 1, 2 };
 GLfloat g_colour_buffer_data[] = { 0.039f, 0.186f, 0.059f };
 // All of these should be overwitten, otherwise it will print a triangle
}

// The cube sizes will inherit from here
void draw(vec3 position)
{
	//--------------------------------------//
	// The initialising section of cube.cpp //
	//--------------------------------------//

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = shader.LoadShaders("shaders/vertex.vs", "shaders/FragmentShader.fragmentshader");

	// This will identify our buffer
	GLuint vertexbuffer;

	// Generates 1 buffer, puts the resulting identifier in the buffer
	glGenBuffers(1, &vertexbuffer);

	// The following commands will talk about our buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer), element_buffer, GL_STATIC_DRAW);

	// Prepare for the "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	//---------------------------------//
	// For drawing section of cube.cpp //
	//---------------------------------//
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shaders
	glUseProgram(programID);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match 	the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	
	// Draws the triangles
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
}