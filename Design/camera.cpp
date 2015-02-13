//Player/Camera Class
// It is worth noting that Lord Tuckey has a better understanding
//  of using the mouse to look around, and might be best to consult him.

bool jump = false;  // Tells controls that player is jumping
int stop = 0;		// Controls the jumps height
vec3 position


void controls()
{ //Obviously not finished, still needs a lot of code to be added and to initialise some variables
  // but this start will make it easier to tackle when he begin working.

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