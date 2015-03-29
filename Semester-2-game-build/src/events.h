#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>
#include "camera.h"

class Events
{
public:
	void handleEvents(SDL_Event * event);
private:
	Camera userInput;
};

#endif //LARGECUBEASSET_H

