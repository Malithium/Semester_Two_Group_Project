#ifndef SMALLCUBEASSET_H
#define SMALLCUBEASSET_H
#define GLM_FORCE_RADIANS

// Library to store the cube positions
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <boost/program_options.hpp>
#include <src/camera.h>
#include <src/gameAsset.h>

using namespace glm;

class SmallCubeAsset : public GameAsset {
	public:
	  explicit SmallCubeAsset();
	 ~SmallCubeAsset();
	 virtual void Draw(GLuint);
	 virtual void NewPosition(vec3);

	private:
	 vec3 position;
	 Camera player;
	 GLuint VertexArrayID, MatrixID;
	 GLuint vertexbuffer, elementbuffer, colourbuffer;
	 mat4 ModelMatrix, ViewMatrix, ProjectionMatrix, MVP;
};

#endif //SMALLCUBEASSET_H
