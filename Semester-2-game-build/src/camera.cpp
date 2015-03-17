#include "camera.h"

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	//The variables we will be using to get the deltaTime
	int currentTime = 0;
	float d_time = 0.0f;
	int previousTime = 0;

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
*@bug 
*for whatever reason, printing out the angle values fixes the lag issue
*/

//The angles we will be using
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;

//our position vector
glm::vec3 position = glm::vec3(0,2,0);

void Camera::cameraControls(SDL_Window* window, SDL_Event &event){
	float speed = 45.0f;
	float mouseSpeed = 0.001f;
	int xpos, ypos;
	int midX, midY;
	float dTime = deltaTime();

	//store the screen's size into these variables;
	SDL_GetWindowSize(window, &midX, &midY);

	//divide the values by 2 in order to get the screens center
	midX = midX / 2;
	midY = midY / 2;

	//disable the cursor so it is not visible;
	SDL_ShowCursor(SDL_DISABLE);
	
	if (event.type == SDL_MOUSEMOTION){
		SDL_GetMouseState(&xpos, &ypos);
		horizontalAngle += mouseSpeed * dTime * float(midX - xpos);
		verticalAngle += mouseSpeed * dTime * float(midY - ypos);
	}
	//stops the camera from going upside down
	if (verticalAngle < -0.6f){
		verticalAngle = -0.6f;
	}
	else if (verticalAngle > 0.6f){
		verticalAngle = 0.6f;
	}
	
	glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	glm::vec3 right = glm::vec3(sin(horizontalAngle) - 3.14f / 2, 0, cos(horizontalAngle) - 3.14f / 2);
	glm::vec3 up = glm::cross(right, direction);

	int y = position.y; // This will allow us to edit the y axis for jumping
	
	// Jump mechanix here

	//detect wether the w,a,s,d keys have been pressed or are being held, and move the camera
	if (event.type == SDL_KEYDOWN){
		switch (event.key.keysym.sym){
		case SDLK_w:
			position += direction * dTime * speed; // Meh
			position.y = y;
			break;
		case SDLK_s:	
			position -= direction * dTime * speed; // A okay
			position.y = y;
			break;
		case SDLK_d:
			position += direction.x * dTime * speed; // A bit off
			position.y = y;
			break;
		case SDLK_a:
			position -= direction.x * dTime * speed; // A bit odd
			position.y = y;
			break;
		}

	}

	float FoV = 45.0f;
	projectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(position, position + direction, up);
}
