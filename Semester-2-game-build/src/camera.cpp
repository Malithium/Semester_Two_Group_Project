#include "camera.h"

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	//The variables we will be using to get the deltaTime
	double currentTime = 0.0;
	float d_time = 0.0f;
	double previousTime = 0;

	//The angles we will be using
	float horizontalAngle = 0.0f;
	float verticalAngle = 0.0f;

	//our position vector
	glm::vec3 position = glm::vec3(0,0,0);

float Camera::deltaTime(){
	currentTime = SDL_GetTicks();
	d_time = float(currentTime - previousTime)/1000;
	previousTime = currentTime;
	return d_time;
}

glm::mat4 Camera::getProjectionMatrix(){
	return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix(){
	return viewMatrix;
}

/*
*
*@bug mouse movement lags the game out massively at the moment
*
*/

void Camera::cameraControls(SDL_Window* window, SDL_Event &event){
	float speed = 1.0f;
	float mouseSpeed = 0.003f;
	int xpos, ypos;
	int midX, midY;

	//store the screen's size into these variables;
	SDL_GetWindowSize(window, &midX, &midY);

	//divide the values by 2 in order to get the screens center
	midX = midX / 2;
	midY = midY / 2;

	//get the x and y position of our mouse
	SDL_GetMouseState(&xpos, &ypos);

	//warp the mouse to the center of the screen
	SDL_WarpMouseInWindow(window, midX, midY);

	//disable the cursor so it is not visible;
	SDL_ShowCursor(SDL_DISABLE);

	//calculate the screens new angles based on the mouse's position 
	horizontalAngle += mouseSpeed * float(midX - xpos);
	verticalAngle += mouseSpeed * float(midY - ypos);

	
	glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	glm::vec3 right = glm::vec3(sin(horizontalAngle) - 3.14f / 2, 0, cos(horizontalAngle) - 3.14f / 2);
	glm::vec3 up = glm::cross(right, direction);

	///detect wether the w,a,s,d keys have been pressed or are being held, and move the camera
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
		case SDLK_w:
			position += direction * deltaTime() * speed;
			break;
		case SDLK_s:
			position -= direction * deltaTime() * speed;
			break;
		case SDLK_d:
			position += right * deltaTime() * speed;
			break;
		case SDLK_a:
			position -= right * deltaTime() * speed;
			break;
		}

	}

	float FoV = 45.0f;
	projectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(position, position + direction, up);

}

//dunjun
