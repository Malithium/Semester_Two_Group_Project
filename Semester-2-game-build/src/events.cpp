#include "events.h"

void Events::handleEvents(SDL_Event * event){
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	switch (event->type){
	case SDL_MOUSEMOTION:
		userInput.mouseMovement();
		break;
	}
	
	 if (currentKeyStates[SDL_SCANCODE_W]){userInput.moveForward();}
     if (currentKeyStates[SDL_SCANCODE_S]){ userInput.moveBackward();}
	 if (currentKeyStates[SDL_SCANCODE_SPACE]){ userInput.jumping();}
	 if (currentKeyStates[SDL_SCANCODE_ESCAPE]){ std::exit(1); }
}
