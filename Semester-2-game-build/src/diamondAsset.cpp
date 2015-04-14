
#include <diamondAsset.h>

DiamondAsset::DiamondAsset() {

	// The 1.25f & -0.25f are designed to make the crystal tall/thin, rather than small/thick 
 	static const GLfloat vertex_buffer[] = {
		 0.0f,  1.25f, 0.0f,
		 0.25f, 0.5f, -0.25f,
		 0.0f, -0.25f, 0.0f,
		-0.25f, 0.5f, -0.25f,
		 0.0f,  1.25f, 0.0f,
		 0.25f, 0.5f,  0.25f,
		 0.0f, -0.25f, 0.0f,
		-0.25f, 0.5f,  0.25f
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
		colour_buffer[3*i+0] = 0.185f;
		colour_buffer[3*i+1] = 0.242f;
		colour_buffer[3*i+2] = 1.0f;
	};

// http://colors.findthedata.com/q/68/10857/What-are-the-RGB-values-of-Diamond
	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// This will identify our buffer
	glGenBuffers(1, &vertexbuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);

	glGenBuffers(1, &elementbuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffers);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_buffer), element_buffer, GL_STATIC_DRAW);

	glGenBuffers(1, &colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colour_buffer), colour_buffer, GL_STATIC_DRAW);

	bbox = make_shared<Bounding>(Bounding(position, 0.5f, 1.5f, 0.5f));
}

DiamondAsset::~DiamondAsset() {
	bbox.reset();
  	// Cleans up by deleting the buffers
	glDeleteBuffers(1, &vertexbuffers);
	glDeleteBuffers(1, &elementbuffers);
	glDeleteBuffers(1, &colourbuffer);;
	glDeleteVertexArrays(1, &VertexArrayID);
}

void DiamondAsset::Draw(GLuint programID, Camera player)
{	
	// Use our shaders
	glUseProgram(programID);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers);
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
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void DiamondAsset::NewPosition(vec3 pos)
{
	position = pos;
	bbox->SetCentre(pos);
}

bool DiamondAsset::Collides(const shared_ptr<Bounding> b)
{
	return bbox->CollidesWith(b);
}

vec3 DiamondAsset::GetPos()
{
	return position;
}

std::shared_ptr<Bounding> DiamondAsset::GetBox()
{
	return bbox;
}
