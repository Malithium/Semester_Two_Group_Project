#include "level.h"

bool Level::runLevel(int lvl, SDL_Window* window)
{
	running = true;   // Will determine if the level loop is still running
	bool gravity = false;

	SDL_Event windowEvent; // Setup SDL windowEvent for game loop
	Events event_handler;

	// The method will fill the cubepositions vector, the If statement is for error checking
	if (fillVector(lvl) == false)
	{
		std::cout << "Problem with file input" << std::endl;
		return false;
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

	// Makes the asset_manager vector implement GameAssetManager functions
	asset_manager = std::make_shared<GameAssetManager>();
	diamonds = blockPositions();  // Fills the vector with cube assets

	// Creates a bounding box to be redone every frame, as position is always updating
	Pbbox = make_shared<Bounding>(Bounding(player.GetPos(), 1.0f, 1.0f, 1.0f));
	
	glClearColor(0.6f, 1.0f, 1.0f, 0.1f); // Adds a sky blue colour to background, once loadings done
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears current frame, for next frame
	
		player.cameraControls(window); // The camera class
		gravity = collisionDetection();		  // Collision
		player.setGravity(gravity);
		asset_manager->Draw(); 			  // Draw
		if (SDL_PollEvent(&windowEvent))
		{
				event_handler.handleEvents(&windowEvent); // Player input
		}

		SDL_GL_SwapWindow(window);
	} while (running == true);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // This should make the screen go black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player.resetPos();
	asset_manager->Clear(); // Empties the vector of assets
	cubepositions.clear();  // Empties the vector of positions
	return true;		// Load the next level
}

bool Level::fillVector(int lvl)
{
   std::string name; 
   bool filled = false;
   cubepositions.clear(); // A fallback

   switch(lvl)
   { 
     case 1:
     name = "levels/levelOne.json";
     break;

     case 2:
     name = "levels/levelTwo.json";
     break;

     case 3:
     name = "levels/levelThree.json";
     break;

     case 4:
     name = "levels/levelFour.json";
     break;

     case 5:
     name = "levels/levelFive.json";
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

int Level::blockPositions()
{  
   glm::vec3 pos;
   int j = 0;
   int num = 0;
   int d = 0;

   for(int i = 0; i < (cubepositions.size()-1); i += 3)
   {
     while(cubepositions.at(i) == -1.0f && i != cubepositions.size())
     {
	j++;
	i++;	
     }
     // This switch will add assets to the asset manager, using the vector with cube positions to determine the size of each asset. See "levelFormat" in the level folder for more information on cube sizes.
     switch(j)
     {
        case 0:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2));
	// Adds a large cube asset to the asset vector
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3)); 
	// Transitions this cube by pos
	asset_manager->Move(num, pos);
	// Add +1 to the amount of cubes
	cubes++;
	break;

	case 1:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2)); 
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2));
	asset_manager->Move(num, pos);
	cubes++;
	break;

	case 2:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1));
	asset_manager->Move(num, pos);
	cubes++;
	break;

	case 3:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2));
	asset_manager->AddAsset(std::make_shared<DiamondAsset>());
	asset_manager->Move(num, pos);
	// Add +1 to the amount of diamonds
	d++;
	break;

	case 4:
	pos = glm::vec3(cubepositions.at(i), cubepositions.at(i+1), cubepositions.at(i+2));
	asset_manager->AddAsset(std::make_shared<DoorAsset>());
	asset_manager->Move(num, pos);
	// For door position
	break;
     }

   // Increment Num so that it moves onto the next cube
   num++;
   }

  return d;
}

bool Level::collisionDetection()
{
	// Because the player moves, the centre needs to be reset
	Pbbox->SetCentre(player.GetPos());

	// if(player collides with diamond) remove diamond 
	for(int i = diamonds; i > 0; i--)
	{
	  if(asset_manager->Collision(i, Pbbox) == true)
	  {
		asset_manager->Remove((asset_manager->Size()-(i+1))); // Add one for the door, which is the final asset
		i = 0;
	  }
	}

	// if(player collides with door) running = false;
	if(asset_manager->Collision(asset_manager->Size(), Pbbox) == true)
	{
		running = false;
	}

	// if(player collides with boxes) gravity is false 
	for(int i = 0; i < cubes; i++)
	{
	  if(asset_manager->Collision(i, Pbbox) == true)
	  {
		return false;
	  }
	}

	return true;
}
