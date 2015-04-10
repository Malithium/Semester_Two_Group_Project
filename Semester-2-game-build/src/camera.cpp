#include "camera.h"

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
//The angles we will be using
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;

//Jump variables
bool jump, gravity;
int stop = 0;

//our position vector
glm::vec3 position = glm::vec3(0, 2, 0); // Collision with (0, 0, 0) cube is an issue
glm::vec3 direction;

bool collision = false;

float dTime = 0;
float speed = 3.0f;
float jumpspeed = 1.5f;
float mouseSpeed = 0.004f;

int xpos, ypos;
int midX, midY;

float initialVel = 0.0015f;
double fallVal = 0.0f;
int y = position.y;

float Camera::deltaTime(){
	static double lastTime = SDL_GetTicks();
	double currentTime = SDL_GetTicks();
	float dTime = float(currentTime - lastTime) / 1000;
	if (dTime > 0.150f)
	{
		dTime = 0.005f;
	}
	lastTime = currentTime;
	return dTime;
}

float Camera::fallingValue(){
	float timeDecelerator = deltaTime();
	if (position.y >= y + 2){
		fallVal -= initialVel - (timeDecelerator * speed);
		jump = false;
		gravity = true;
	}
	if (jump == true && gravity == false)
		fallVal += initialVel - (timeDecelerator * speed);
	std::cout << timeDecelerator << std::endl;
	std::cout << fallVal << std::endl;
	return fallVal;
}

glm::mat4 Camera::getProjectionMatrix(){
	return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix(){
	return viewMatrix;
}

void Camera::moveForward(){
	dTime = deltaTime();
	position += glm::vec3(direction.x * dTime * speed, 0.0f, direction.z * dTime * speed);
}

void Camera::moveBackward(){
	dTime = deltaTime();
	position -= glm::vec3(direction.x * dTime * speed, 0.0f, direction.z * dTime * speed);
}

void Camera::mouseMovement(){
	dTime = deltaTime();
	SDL_GetMouseState(&xpos, &ypos);
	horizontalAngle += mouseSpeed * dTime / 2 * float(midX - xpos);
	verticalAngle += mouseSpeed * dTime / 2 * float(midY - ypos);
}

void Camera::setJump()
{
	if (jump != true && gravity != true)
	{
		jump = true;
	}
}

void Camera::jumping()
{
	if (gravity == false)
		jump = true;
	dTime = deltaTime();
	position.y += fallingValue(); // This isn't smooth enough
}

bool Camera::inAir(bool air){
	return air;
}

glm::vec3 Camera::GetPos()
{
	return position;
}

void Camera::cameraControls(SDL_Window* window) {
	
	//store the screen's size into these variables;
	SDL_GetWindowSize(window, &midX, &midY);

	//divide the values by 2 in order to get the screens center
	midX = midX / 2;
	midY = midY / 2;
	SDL_WarpMouseInWindow(window, midX, midY);
	//disable the cursor so it is not visible;
	SDL_ShowCursor(SDL_DISABLE);
	//compute the spherical coordinates into cartesian coordinates.
	direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

	float FoV = 45.0f;
	projectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));

}