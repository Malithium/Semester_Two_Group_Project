
#include <DoorAsset.h>

DoorAsset::DoorAsset() {	

	static GLfloat vertex_buffer[] = {
		-0.1f, -1.0f,  0.75f,
	 	 0.1f, -1.0f,  0.75f,
		 0.1f,  1.5f,  0.75f,
		-0.1f,  1.5f,  0.75f,
		-0.1f, -1.0f, -0.75f,
		 0.1f, -1.0f, -0.75f,
		 0.1f,  1.5f, -0.75f,
		-0.1f,  1.5f, -0.75f
	};

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

	static GLfloat colour_buffer[12*3*3];
	for(int i = 0; i < 12*3; i++)
	{
		colour_buffer[3*i+0] = 1.0f;
		colour_buffer[3*i+1] = 1.0f;
		colour_buffer[3*i+2] = 1.0f;
	}
	
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

DoorAsset::~DoorAsset() {
	bbox.reset();
  	// Cleans up by deleting the buffers
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteBuffers(1, &colourbuffer);;
	glDeleteVertexArrays(1, &VertexArrayID);
}

void DoorAsset::Draw(GLuint programID, Camera player)
{	
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
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void DoorAsset::NewPosition(vec3 pos)
{
	position = pos;
	bbox = make_shared<Bounding>(Bounding(position, 1.0f, 3.5f, 1.5f));
}

bool DoorAsset::Collides(const shared_ptr<Bounding> b)
{
	return bbox->CollidesWith(b);
}

vec3 DoorAsset::GetPos()
{
	return position;
}

std::shared_ptr<Bounding> DoorAsset::GetBox()
{
	return bbox;
}
