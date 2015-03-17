#ifndef GAMEASSET_H
#define GAMEASSET_H

#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameAsset {
	public:
	 virtual void Draw(GLuint) = 0;
	 virtual void NewPosition(glm::vec3) = 0;
};

#endif //GAMEASSET_H
