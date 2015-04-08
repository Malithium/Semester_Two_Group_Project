#include "events.h"

void Events::handleEvents(SDL_Event * event){
	static double lastTime = SDL_GetTicks();
	double currentTime = SDL_GetTicks();
	float dTime = float(currentTime - lastTime) / 1000;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); //keyboard input handler

	if (dTime > 0.150f)
	{
		dTime = 0.005f;
	}

	switch (event->type){
	case SDL_MOUSEMOTION:
		userInput.mouseMovement(dTime);
		break;
	}
	
	if (currentKeyStates[SDL_SCANCODE_W]){userInput.moveForward(dTime);}
	else if (currentKeyStates[SDL_SCANCODE_S]){ userInput.moveBackward(dTime);}
	else if (currentKeyStates[SDL_SCANCODE_SPACE]){ userInput.jumping(dTime);}
	else if (currentKeyStates[SDL_SCANCODE_ESCAPE]){ std::exit(1); }
	
	userInput.jumping(dTime); // dTime made this complicated
	lastTime = currentTime;
}
