#ifndef DOORASSET_H
#define DOORASSET_H
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

/**
* This GameAsset is the door which the player will use to transition between
* the levels. Its design is extremely similar to the cube, except that it is
* rectangular instead of cuboid.   
*/

class DoorAsset : public GameAsset {
	public:
	  explicit DoorAsset();
	 ~DoorAsset();
	 virtual void Draw(GLuint programID, Camera player);
	 virtual void NewPosition(vec3);
	 virtual bool Collides(const shared_ptr<Bounding> b);
	 virtual vec3 GetPos();
	 virtual std::shared_ptr<Bounding> GetBox();

	private:
	 vec3 position;
	 GLuint VertexArrayID, MatrixID;
	 GLuint vertexbuffer, elementbuffer, colourbuffer;
	 std::shared_ptr<Bounding> bbox;
};

#endif //DOORASSET_H
