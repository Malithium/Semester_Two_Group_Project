
#include "level.h"

using namespace glm;

void Level::runlevel(int lvl)
{
	bool running = true; // Will determine if the level is still running
	
	// The method will fill the cubepositions vector, the IF statement is there for error checking
	if(fillVector(lvl) = false) 
	{
	   std::cout << "Problem with file input" << std::endl;
	}
	
	do
	{
 	 //glm::mat4 MVP = player(); // The camera class
	 blockpositions();  // Loads cubes onto screen
		
	}
	while(level == true);
	
	cubepositions.clear();
	// I know this won't work atm but we need to sort it out later
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteBuffers(1, &elementbuffer);
	//glDeleteProgram(programID);
	//glDeleteVertexArrays(1, &VertexArrayID);
}

bool Level::fillVector(int lvl)
{
   ifstream input;
   bool filled = false;
   if(! cubepositions.empty())
   {
      cubepositions.clear(); // Fallback
   }

   switch(level)
   { 
     case 1:
     input = input("levelOne.txt", std::ifstream::in);
     filled = true;
     break;

     // Continue for every level - 5 currently
   }

   int done = 0;
   for(int i = 0; done < 3; i++)
   {
      float line;
      getline(input, line);
      cubepositions.push_back(line);
      if(line == NULL)
      {
        done++; // There should be two NULLs, to change cube size, and then a final NULL to signal the end of the file.
      }
   }
   
   return filled;
}

void Level::blockPositions()
{   
   int j = 0;
   for(int i = 0; i < (cubepositions.size()-1); i += 3)
   {
     if(cubepositions.at(i) == NULL)
     {
	j++;
	i++;	
     }
     switch(j)
     {
        case 0:
	glm::vec3 pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); //Theory atm
	//largeCube(pos);
	break;

	case 1:
	glm::vec3 pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); //Theory atm
	//mediumCube(pos);
	break;

	case 2:
	glm::vec3 pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); //Theory atm
	//smallCube(pos);
	break;

	default:
	std::cout << "Problem with Cube Positions" << std::endl;
	break;	
     }

   }
}
