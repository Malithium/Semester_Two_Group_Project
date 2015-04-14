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

class GameAsset {
	public:
	 virtual void Draw(GLuint programID, Camera player) = 0;
	 virtual void NewPosition(glm::vec3) = 0;
	 virtual bool Collides(shared_ptr<Bounding>) = 0;
	 virtual vec3 GetPos() = 0;
	 virtual std::shared_ptr<Bounding> GetBox() = 0;
};

#endif //GAMEASSET_H
