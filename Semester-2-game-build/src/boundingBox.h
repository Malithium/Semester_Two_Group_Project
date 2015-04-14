#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#define GLM_FORCE_RADIANS

#include <iostream>
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

class Bounding {
	public:
	  Bounding(const vec3, float, float, float);
	  virtual ~Bounding();
	  float getWidth();
	  float getHeight();
	  float getLength();
	  void SetCentre(vec3);
	  bool CollidesWith(const shared_ptr<Bounding>);
	  vec3 pos;

	private:
	  float width, height, length;

};

#endif //BOUNDINGBOX_H
