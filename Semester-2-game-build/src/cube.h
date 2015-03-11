#ifndef CUBEASSET_H
#define CUBEASSET_H
#define GLM_FORCE_RADIANS

// Library to store the cube positions
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <boost/program_options.hpp>
#include <src/camera.h>
#include <src/gameAsset.h>

using namespace glm;

class LargeCubeAsset : public GameAsset {
	public:
	  explicit LargeCubeAsset();
	 ~LargeCubeAsset();
	 virtual void Draw(GLuint);

	private:
	 vec3 position;
	 Camera player;
	 GLuint VertexArrayID, MatrixID;
	 GLuint vertexbuffer, elementbuffer, colourbuffer;
};

#endif //CUBEASSET_H
