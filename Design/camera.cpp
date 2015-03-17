//Player/Camera Class
// It is worth noting that Lord Tuckey has a better understanding
//  of using the mouse to look around, and might be best to consult him.

using namespace glm;

bool jump = false;  // Tells controls that player is jumping
int stop = 0;		// Controls the jumps height
vec3 position = vec3(0, 0, 0); // Starting position of the player


void controls()
{ //Obviously not finished, still needs a lot of code to be added and to initialise some variables
  // but this start will make it easier to tackle when we begin working.
  
	//This section deals with window size and mouse positioning
	int midX, midY;
	//Stores the window sizes in these values
	SDL_GetWindowSize(window, &midX, &midY);
	
	midX = midX / 2;
	midY = midY / 2;
  
    //Gets the time of the last frame
	static double lastTime = SDL_GetTicks();
	//Gets the time of the current frame
	double currentTime = SDL_GetTicks();
	//Minus' the current time, by the last time, in order to get the delta time
	float deltaTime = (float)(currentTime - lastTime)/1000; 
	
	//Get the X and Y position of our mouse
	SDL_GetMouseState(&xpos, &ypos);
	//Warps the mouse to the centre of the screen
	SDL_WarpMouseInWindow(window, midX, midY);
	//Disables the cursor so it isn't visible;
	SDL_ShowCursor(SDL_DISABLE);
 
	if(gravity == true)
	{
		y -= 0.05f; // An issue for later
	}

	// This section deals with jumping
	if(jump != true && gravity != true && event.type == SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_space:
				jump = true;
				break;
		}
	}
	if(jump == true && stop != 6)  // IF statement needed to increase Y direction
	{
		position += vec3(0, 1, 0);
		stop++;
	}
	else							//	Else used to stop jumping
	{
		jump = false;
		stop = 0;
	}

	// This section deals with moving the character (W,A,S,D)
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
			case SDLK_w:
				// Insert code here
				break;
			case SDLK_s:
				// Insert code here
				break;
			case SDLK_d:
				// Insert code here
				break;
			case SDLK_a:
				// Insert code here
				break;
		}
	}
	// This section deals with jumping
	if(jump != true && gravity != true && event.type == SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
			case SDLK_space:
				jump = true;
				break;
		}
	}
	if(jump == true && stop != 6)  // IF statement needed to increase Y direction
	{
		position += vec3(0, 1, 0);
		stop++;
	}
	else							//	Else used to stop jumping
	{
		jump = false;
		stop = 0;
	}
	// This section deals with camera positioning and direction
	
	
}
