#include "camera.h"

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

//Jump variables
bool jump, gravity;

//our position vector
glm::vec3 position = glm::vec3(0, 2, 0);
glm::vec3 direction;

//The angles we will be using
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;
float decVelocity;

float speed = 3.0f;
float jumpspeed = 0.0018f;
float fallingSpeed = 0.0018f;
float startingVelocity = 0.09;
float mouseSpeed = 0.0036f;

int xpos, ypos;
int midX, midY;
int y = position.y;

/**
* Need for translating cubes from model to world space
*/
glm::mat4 Camera::getProjectionMatrix(){
	return projectionMatrix;
}

/**
* Need for translating cubes from model to world space
*/
glm::mat4 Camera::getViewMatrix(){
	return viewMatrix;
}

/**
* If W is pressed then camera moves forward, based on where the camera is facing. Y is moved by 0.0f (So it doesn't move)
*/
void Camera::moveForward(float dTime){
	position += glm::vec3(direction.x * dTime * speed, 0.0f, direction.z * dTime * speed);
}

/**
* If S is pressed then camera moves forward, based on where the camera is facing. Y is moved by 0.0f (So it doesn't move)
*/
void Camera::moveBackward(float dTime){
	position -= glm::vec3(direction.x * dTime * speed, 0.0f, direction.z * dTime * speed);
}

/**
* Uses the mouses position to determine where the camera is looking
*/
void Camera::mouseMovement(float dTime){
	SDL_GetMouseState(&xpos, &ypos);
	horizontalAngle += mouseSpeed * dTime / 2 * float(midX - xpos);
	verticalAngle += mouseSpeed * dTime / 2 * float(midY - ypos);
}

/**
* Returns the status of gravity
*/
bool Camera::currentlyFalling(){
	return gravity;
}

/**
* Sets jump to true or false
*/
void Camera::setJump(bool j)
{
	jump = j;
}

/**
* Sets gravity to true or false
*/
void Camera::setGravity(bool g)
{
	gravity = g;
}

/**
* Resets the position of the gravity
*/
void Camera::resetPos(){
	position = glm::vec3(0, 2, 0);
}

/**
* If jumping is true then Y is incremented by dTime * speed, but if it exceeds Y + 2 then stop jumping
*/
void Camera::jumping(float dTime)
{
	if (position.y > y + 2)
		jump = false;
	if (jump == true){
		if (dTime > 0.150)
			dTime = 0.005;
		position.y += dTime * speed;
	}
}

/**
* Y decrements by dTime * speed
*/
void Camera::falling(float dTime)
{
	position.y -= dTime * speed;
}

/**
* Returns the cameras current position
*/
glm::vec3 Camera::GetPos()
{
	return position;
}

/**
* Several things occur here, but its main purpose is to update the camera position and direction 
*  as well as manage variables like jumping and gravity
*/
void Camera::cameraControls(SDL_Window* window) {
	static double lastTime = SDL_GetTicks();
	double currentTime = SDL_GetTicks();
	float dTime = float(currentTime - lastTime) / 1000;
	//store the screen's size into these variables;
	SDL_GetWindowSize(window, &midX, &midY);
	//divide the values by 2 in order to get the screens center
	midX = midX / 2;
	midY = midY / 2;
	SDL_WarpMouseInWindow(window, midX, midY);

	if (gravity == true && jump == false)
		falling(dTime);

	if (position.y <= -8)
		resetPos();

	if (gravity == false)
		y = position.y;
	//disable the cursor so it is not visible;
	SDL_ShowCursor(SDL_DISABLE);
	//compute the spherical coordinates into cartesian coordinates.
	direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	//std::cout << position.z << std::endl;
	float FoV = 45.0f;
	projectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
	lastTime = currentTime;
}
