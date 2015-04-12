#include "events.h"

void Events::handleEvents(SDL_Event * event){
	static double lastTime = SDL_GetTicks();
	double currentTime = SDL_GetTicks();
	float dTime = float(currentTime - lastTime) / 1000;
	if (dTime > 0.150)
		dTime = 0.005;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	bool gCheck = userInput.currentlyFalling();
	switch (event->type){
	case SDL_MOUSEMOTION:
		userInput.mouseMovement(dTime);
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym){
		case SDLK_SPACE:
			userInput.setJump(false);
		}
	default:
		userInput.falling();
		break;
	}
	
	 if (currentKeyStates[SDL_SCANCODE_W]){userInput.moveForward(dTime);}
	 if (currentKeyStates[SDL_SCANCODE_S]){userInput.moveBackward(dTime);}
	 if (currentKeyStates[SDL_SCANCODE_SPACE]){
		 if (gCheck == false)
			userInput.setJump(true); 
	 userInput.jumping(dTime);
	 }
	 if (currentKeyStates[SDL_SCANCODE_ESCAPE]){ std::exit(1); }

	 lastTime = currentTime;
}