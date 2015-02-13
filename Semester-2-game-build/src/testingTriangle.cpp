 // Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <src/shader.hpp>
 
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
}

while() 
{
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

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
 }

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colourbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);