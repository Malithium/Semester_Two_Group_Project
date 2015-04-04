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
#include <src/boundingBox.h>

using namespace glm;

class CubeAsset : public GameAsset {
	public:
	  explicit CubeAsset(int num);
	 ~CubeAsset();
	 virtual void Draw(GLuint);
	 virtual void NewPosition(vec3);
	 virtual bool Collides(const shared_ptr<Bounding> b);
	 virtual std::shared_ptr<Bounding> GetBox();

	private:
	 vec3 pos;
	 Camera player;
	 int number;
	 GLuint VertexArrayID, MatrixID;
	 GLuint vertexbuffer, elementbuffer, colourbuffer;
	 std::shared_ptr<Bounding> bbox;
};

#endif //CUBEASSET_H
