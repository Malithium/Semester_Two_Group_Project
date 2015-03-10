#ifndef GAMEASSET_H
#define GAMEASSET_H

#include <iostream>
#include <GL/gl.h>

class GameAsset {
	public:
	 virtual void Draw(GLuint) = 0;
};

#endif //GAMEASSET_H
