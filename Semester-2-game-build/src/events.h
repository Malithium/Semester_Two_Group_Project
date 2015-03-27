#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>
#include "camera.h"

class events
{
public:
	void handleEvents(SDL_Event * event);
private:
	controls userInput;
};

#endif //LARGECUBEASSET_H

