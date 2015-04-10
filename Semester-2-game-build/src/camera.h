#ifndef CAMERA_H
#define CAMERA_H
#define GLM_FORCE_RADIANS

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera
{

public:
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	void moveForward();
	void moveBackward();
	void mouseMovement();

	float deltaTime();
	float fallingValue();

	void setJump();
	void resetPos();
	void jumping();
	void falling(bool g);

	bool inAir(bool air);
	glm::vec3 GetPos();
	void cameraControls(SDL_Window* window);

private:
};

#endif //CAMERA_H