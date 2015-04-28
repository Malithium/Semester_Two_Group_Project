#ifndef GAMEASSET_H
#define GAMEASSET_H

#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <src/camera.h>
#include <src/boundingBox.h>

/**
* Creates a standard for the gameassetmanager to create a vector of this types
* allowing it to store the different cube types, such as diamonds and doors, in
* a single vector. 
*/

class GameAsset {
	public:
	 virtual void Draw(GLuint programID, Camera player) = 0;
	 virtual void NewPosition(glm::vec3) = 0;
	 virtual bool Collides(shared_ptr<Bounding>) = 0;
	 virtual vec3 GetPos() = 0;
	 virtual std::shared_ptr<Bounding> GetBox() = 0;
};

#endif //GAMEASSET_H
