
#include "level.h"

bool Level::runLevel(int lvl, SDL_Window* window)
{
	bool running = true;   // Will determine if the level is still running
	SDL_Event windowEvent; //setup SDL windowEvent and game loop
	
	// The method will fill the cubepositions vector, the IF statement is there for error checking
	if(fillVector(lvl) == false) 
	{
	   std::cout << "Problem with file input" << std::endl;
	}
	
	do {
 	 Camera player.cameraControls(window, windowEvent) // The camera class
	 blockPositions();  // Loads cubes onto screen
	 // Diamond stuff goes here
	 if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) return false;
		}
	 SDL_GL_SwapWindow(window);
	}
	while(running == true);
	
	cubepositions.clear();
	return true;
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
