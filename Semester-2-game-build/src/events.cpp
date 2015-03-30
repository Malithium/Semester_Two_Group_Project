#include "events.h"

void Events::handleEvents(SDL_Event * event){
	static double lastTime = SDL_GetTicks();
	double currentTime = SDL_GetTicks();
	float dTime = float(currentTime - lastTime) / 1000;


	if (dTime > 0.150f)
	{
		dTime = 0.005f;
	}

	switch (event->type){
	case SDL_QUIT:
	case SDL_MOUSEMOTION:
		userInput.mouseMovement(dTime);
		break;
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym){
		case SDLK_w:
			userInput.moveForward(dTime);
			break;
		case SDLK_s:
			userInput.moveBackward(dTime);
			break;
		case SDLK_SPACE:
			userInput.setJump();
			break;
		case SDLK_ESCAPE:
			std::exit(1);
			break;
		}
		break;
	}
	
	userInput.jumping(dTime); // dTime made this complicated
	lastTime = currentTime;
}
