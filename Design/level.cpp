// Class to load the levels
#include <vector>;

using namespace glm;

void levelLoader(int level)
{
	switch(level)
	{
		case 1:
		levelOne();
		break;
		
		case 2:
		levelTwo();
		break;
		
		default:
		cout << "Level unable to load" << endl;
	}
}

void levelOne()
{
	bool running = true; // Will determine if the level is still running
	
	// This vector will read in vec3s from a .txt document with the cube positions
	//  which makes the levels easier to edit and manage.
	std::vector<vec3>cubepositions();
	
	do
	{
 	 glm::mat4 MVP = player(); // The camera class
	 
		
	}
	while(level == true);
	
	// I know this won't work atm but need to sort it out later
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void levelTwo()
{
	bool running = true; // Will determine if the level is still running
	//Will hold vectors with information on cube placements (So will load the level)

	do
	{
		
	}
	while(level == true);
}
