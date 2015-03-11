
#include "level.h"

bool Level::runLevel(int lvl, SDL_Window* window)
{
	bool running = true;   // Will determine if the level is still running
	SDL_Event windowEvent; // Setup SDL windowEvent for game loop
	Camera player;
	
	// The method will fill the cubepositions vector, the If statement is for error checking
	if(fillVector(lvl) == false) 
	{
	   std::cout << "Problem with file input" << std::endl;
	   return false;
	}

	asset_manager = std::make_shared<GameAssetManager>();
	blockPositions();  	// Fill vector with cube assets

	do {
	 player.cameraControls(window, windowEvent); // The camera class
	 asset_manager->Draw(); // Loads cubes onto screen
	 // Diamond stuff goes here
	 if (SDL_PollEvent(&windowEvent)) //Press Esc to close the game
	 {
		if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) 
		{
			return false;
		}
	 }
	 SDL_GL_SwapWindow(window);
	}
	while(running == true);
	
	cubepositions.clear(); // Empties the vector of positions
	return true;
}

bool Level::fillVector(int lvl)
{
   std::string name; 
   bool filled = false;
   if(cubepositions.empty())
   {
      cubepositions.clear(); // A fallback
   }

   switch(lvl)
   { 
     case 1:
     name = "levels/levelOne.json";
     break;

     // Continue for every level - 5 currently
   }

   std::ifstream input(name, std::ifstream::in);
   std::string line; 
   std::string::size_type sz; // Allows for String to float conversion

   while(true) // There should be three -1.0fs, to change cube size, and then an END to signify the end of the file.
   {
      getline(input, line);
      if(line == "END") //The final position, to signify the end of the file.
      {
	filled = true;
	break;
      }
      float in = std::stof(line, &sz); //String to float conversion
      cubepositions.push_back(in);
   }
   
   return filled;
}

void Level::blockPositions()
{  
   glm::vec3 pos;
   int j = 0;
   for(int i = 0; i < (cubepositions.size()-1); i += 3)
   {
     while(cubepositions.at(i) == -1.0f && i != cubepositions.size())
     {
	j++;
	i++;	
     }
     switch(j)
     {
        case 0:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); //Theory atm
	asset_manager->AddAsset(std::make_shared<LargeCubeAsset>());
	break;

	case 1:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); //Theory atm
	//MediumCube mediumCube.draw(pos);
	break;

	case 2:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); //Theory atm
	//SmallCube smallCube.draw(pos);
	break;

	case 3:
	//pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2));
	
	// For door position - probably won't be in this section of the code
	break;
     }
   }
}
