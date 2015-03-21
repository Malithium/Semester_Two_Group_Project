
#include <diamondAsset.h>

DiamondAsset::DiamondAsset() {

	// The 1.5f & -0.5f are designed to make the crystal tall/thin, rather than small/thick 
 	static const GLfloat vertex_buffer[] = {
		 0.0f,  1.5f,  0.0f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.0f, -0.5f,  0.0f,
 	};

 	static const GLuint element_buffer[] = {
		1, 0, 2,
		2, 5, 1,
		2, 0, 3,
		3, 5, 2,
		3, 0, 4,
		4, 5, 3,
		4, 0, 1,
		1, 5, 4
 	};	

	static GLfloat colour_buffer[12*3*3];
	for(int i = 0; i < 12*3; i++)
	{
		colour_buffer[3*i+0] = 0.185f;
		colour_buffer[3*i+1] = 0.242f;
		colour_buffer[3*i+2] = 0.255f;
	};

// http://colors.findthedata.com/q/68/10857/What-are-the-RGB-values-of-Diamond
	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// This will identify our buffer
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer), element_buffer, GL_STATIC_DRAW);

	glGenBuffers(1, &colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colour_buffer), colour_buffer, GL_STATIC_DRAW);
}

DiamondAsset::~DiamondAsset() {
  	// Cleans up by deleting the buffers
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteBuffers(1, &colourbuffer);;
	glDeleteVertexArrays(1, &VertexArrayID);
}

void DiamondAsset::Draw(GLuint programID)
{	
	// Use our shaders
	glUseProgram(programID);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. Must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stridea
		(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glVertexAttribPointer(
		1,                  // attribute 1. Must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	
	// Prepare for the "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	mat4 ProjectionMatrix = player.getProjectionMatrix();
	mat4 ViewMatrix = player.getViewMatrix();
	mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), position);
	mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// Draws the triangles
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void DiamondAsset::NewPosition(vec3 pos)
{
	position = pos;
}
