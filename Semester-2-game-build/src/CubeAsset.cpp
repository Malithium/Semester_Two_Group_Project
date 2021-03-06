
#include <CubeAsset.h>

CubeAsset::CubeAsset(int num) {	

	static GLfloat vertex_buffer[3*8];
	for(int i = 0; i < 8; i++)
	{
	  if( i == 0 || i == 3 || i == 4 ||i == 7) //Negative numbers for X vertexs
	  {
		vertex_buffer[3*i+0] = (-1.0f * num);
	  }
	  else
	  {
		vertex_buffer[3*i+0] = (1.0f * num);
	  }

	  if( i == 0 || i == 1 || i == 4 ||i == 5) //Negative numbers for Y vertexs
	  {
		vertex_buffer[3*i+1] = -1.0f;
	  }
	  else
	  {
		vertex_buffer[3*i+1] = 1.0f;
	  }

	  if( i >= 4 ) //Negative numbers for Z vertexs
	  {
		vertex_buffer[3*i+2] = (-1.0f * num);
	  }
	  else
	  {
		vertex_buffer[3*i+2] = (1.0f * num);
	  }
	}
	number = num;

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
	  if( i == 0 || i == 1 || i == 4 ||i == 5)
	  {
		colour_buffer[3*i+0] = 0.140f;
		colour_buffer[3*i+1] = 0.059f;
		colour_buffer[3*i+2] = 0.038f;
	  }
	  else
	  {
		colour_buffer[3*i+0] = 0.039f;
		colour_buffer[3*i+1] = 0.255f;
		colour_buffer[3*i+2] = 0.059f;
	  }
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

	float size = (2.0f * number) - 1.0f;
	bbox = make_shared<Bounding>(Bounding(position, size, 2.0f, size));
}

CubeAsset::~CubeAsset() {
	bbox.reset();
  	// Cleans up by deleting the buffers
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteBuffers(1, &colourbuffer);;
	glDeleteVertexArrays(1, &VertexArrayID);
}

/**
* Draws the cubes onto the screen
*/
void CubeAsset::Draw(GLuint programID, Camera player)
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

/**
* Sets a new translating position, as well as a switch to handle BB issue
*/
void CubeAsset::NewPosition(vec3 pos)
{
	position = pos;
	// Regarding issues with BB, moving the centre point to the top left corner fixes problems where the player would fall through the floor.
	switch(number)
	{
		case 1:
		bbox->SetCentre(pos);
		break;
		
		case 2:
		pos.x -= 1.0f;
		pos.z -= 1.0f;
		bbox->SetCentre(pos);
		break;

		case 3:
		pos.x -= 2.0f;
		pos.z -= 2.0f;
		bbox->SetCentre(pos);
		break;
	}
}

/**
* Returns true if two things are colliding
*/
bool CubeAsset::Collides(const shared_ptr<Bounding> b)
{
	return bbox->CollidesWith(b);
}

/**
* Returns the cubes position
*/
vec3 CubeAsset::GetPos()
{
	return position;
}

/**
* Obtains the assets BB
*/
std::shared_ptr<Bounding> CubeAsset::GetBox()
{
	return bbox;
}
