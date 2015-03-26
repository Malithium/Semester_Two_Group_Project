#include "camera.h"
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

glm::mat4 Camera::getProjectionMatrix(){
	return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix(){
	return viewMatrix;
}

//The angles we will be using
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;
//our position vector
glm::vec3 position = glm::vec3(0,2,0);

void Camera::cameraControls(SDL_Window* window, SDL_Event *event){
	static double lastTime = SDL_GetTicks();
	double currentTime = SDL_GetTicks();
	float dTime = float(currentTime - lastTime)/1000;

	float speed = 3.0f;
	float mouseSpeed = 0.0015f;
	int xpos, ypos;
	int midX, midY;

	if(dTime > 0.150f)
	{
		dTime = 0.005f;
	}

	//store the screen's size into these variables;
	SDL_GetWindowSize(window, &midX, &midY);

	//divide the values by 2 in order to get the screens center
	midX = midX / 2;
	midY = midY / 2;

	//disable the cursor so it is not visible;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_WarpMouseInWindow(window,midX,midY);

	glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

	int y = position.y; // This will allow us to edit the y axis for jumping

	// Jump mechanix here

	//detect wether the w,a,s,d keys have been pressed or are being held, and move the camera
	if (event->type == SDL_KEYDOWN){
		switch (event->key.keysym.sym){
		case SDLK_w:
			position += direction * dTime * speed; // Meh
			position.y = y;
			break;
		case SDLK_s:
			position -= direction * dTime * speed; // A okay
			position.y = y;
			break;
		}
	}
	else if (event->type == SDL_MOUSEMOTION){
		SDL_GetMouseState(&xpos, &ypos);
		horizontalAngle += mouseSpeed * dTime/2 * float(midX - xpos);
		verticalAngle += mouseSpeed * dTime/2 * float(midY - ypos);
		//event->type = SDL_IGNORE;
	}

	float FoV = 45.0f;
	projectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0,1,0));
	lastTime = currentTime;
}
