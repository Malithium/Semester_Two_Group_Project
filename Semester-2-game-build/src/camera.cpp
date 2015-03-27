#include "camera.h"

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
//The angles we will be using
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;

//our position vector
glm::vec3 position = glm::vec3(0, 2, 0);
glm::vec3 direction;

float speed = 3.0f;
float mouseSpeed = 0.0015f;

int xpos, ypos;
int midX, midY;

int y = position.y; // This will allow us to edit the y axis for jumping

glm::mat4 Camera::getProjectionMatrix(){
	return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix(){
	return viewMatrix;
}

void Camera::moveForward(float dtime){
	position += direction * dtime * speed; 
	position.y = y;
}

void Camera::moveBackward(float dtime){
	position -= direction * dtime * speed; 
	position.y = y;
}

void Camera::mouseMovement(float dtime){
	SDL_GetMouseState(&xpos, &ypos);
	horizontalAngle += mouseSpeed * dtime / 2 * float(midX - xpos);
	verticalAngle += mouseSpeed * dtime / 2 * float(midY - ypos);
}

void Camera::cameraControls(SDL_Window* window){
	//store the screen's size into these variables;
	SDL_GetWindowSize(window, &midX, &midY);

	//divide the values by 2 in order to get the screens center
	midX = midX / 2;
	midY = midY / 2;

	//disable the cursor so it is not visible;
	SDL_ShowCursor(SDL_DISABLE);

	//compute the spherical coordinates into cartesian coordinates.
	direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

	float FoV = 45.0f;
	projectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
	
}

