
#include "level.h"

void Level::runLevel(int lvl)
{
	bool running = true; // Will determine if the level is still running
	
	// The method will fill the cubepositions vector, the IF statement is there for error checking
	if(fillVector(lvl) == false) 
	{
	   std::cout << "Problem with file input" << std::endl;
	}
	
	do
	{
 	 //glm::mat4 MVP = player(); // The camera class
	 blockPositions();  // Loads cubes onto screen
		
	}
	while(running == true);
	
	cubepositions.clear();
	// I know this won't work atm but we need to sort it out later
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteBuffers(1, &elementbuffer);
	//glDeleteProgram(programID);
	//glDeleteVertexArrays(1, &VertexArrayID);
}

bool Level::fillVector(int lvl)
{
   std::ifstream input("levels/levelOne.json", std::ifstream::in);
   bool filled = false;
   if(cubepositions.empty())
   {
      cubepositions.clear(); // Fallback
   }

   switch(lvl)
   { 
     case 1:
     //input = input;
     filled = true;
     break;

     // Continue for every level - 5 currently
   }

   int done = 0;
   std::string line; 
   std::string::size_type sz; // Allows for String to float conversion
   for(int i = 0; done < 3; i++)
   {
      getline(input, line);
      float in = std::stof(line, &sz);
      cubepositions.push_back(in);
      if(line == "-1.0f")
      {
	// There should be two -1.0fs, to change cube size, and then a final -1.0f to signal the end of the file.
        done++;
      }
   }
   
   return filled;
}

void Level::blockPositions()
{  
   glm::vec3 pos;
   int j = 0;
   for(int i = 0; i < (cubepositions.size()-1); i += 3)
   {
     if(cubepositions.at(i) == -1.0f)
     {
	j++;
	i++;	
     }
     switch(j)
     {
        case 0:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); //Theory atm
	LargeCube largeCube.draw(pos);
	break;

	case 1:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); //Theory atm
	//MediumCube mediumCube.draw(pos);
	break;

	case 2:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); //Theory atm
	//SmallCube smallCube.draw(pos);
	break;
     }

   }
}
