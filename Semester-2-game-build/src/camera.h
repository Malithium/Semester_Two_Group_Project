#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{

public:
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	float deltaTime();
	void cameraControls(SDL_Window* window, SDL_Event &event);
private:

};
