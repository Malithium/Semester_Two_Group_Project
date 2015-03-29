#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#define GLM_FORCE_RADIANS

#include <memory>
#include <utility>
#include <ostream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

enum AXIS {X, Y, Z};

class Bounding {
	public:
	  Bounding(const vec3, const float, const float, const float);
	  ~Bounding();
	  bool CollidesWith(const shared_ptr<Bounding>);

	private:
	  shared_ptr<vec3> centre, extent_x, extent_y, extent_z;

	  vec3 projectOntoAxis(const Bounding &, enum AXIS);

};

#endif //BOUNDINGBOX_H
