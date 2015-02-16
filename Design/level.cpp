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
	//Will hold vectors with information on cube placements (So will load the level)
	std::vector<vec3>cubepositions((0.0f, 0.0f, 0.0f), (6.0f, 0.0f, 0.0f),(0.0f, 0.0f, 6.0f), (6.0f, 0.0f, 6.0f), 
	(NULL, NULL, NULL), 
	(NULL, NULL, NULL)); //No idea if this spacing will work
	
	do
	{
		
	}
	while(level == true);
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