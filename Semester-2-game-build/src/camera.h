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
	//Matrix methods
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();

	//Camera Movement methods
	void moveForward(float dt);
	void moveBackward(float dt);
	void mouseMovement(float dt);
	void jumping();

	void getDeltaTime(float dt);
	void setJump();
	void setGravity(bool g);
	void resetPos();

	void falling();

	glm::vec3 GetPos();
	void cameraControls(SDL_Window* window);

private:
};

#endif //CAMERA_H