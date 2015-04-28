#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>
#include "camera.h"

/**
* Events is responsible for handling the inputs from the keyboard and the 
* mouse. It also has its own delta time, to help make the game run smoothly. 
*/
class Events
{
	public:
	 bool handleEvents(SDL_Event * event);
	private:
	 Camera userInput;
};

#endif //LARGECUBEASSET_H

