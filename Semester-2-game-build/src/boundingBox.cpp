#include "boundingBox.h"

Bounding::Bounding(const vec3 centre, const float width, const float height, const float length) :
	centre(make_shared<vec3>(centre)),
	extent_x(make_shared<vec3>(vec3(width/2, 0, 0))),
	extent_y(make_shared<vec3>(vec3(0, height/2, 0))),
	extent_z(make_shared<vec3>(vec3(0, 0, length/2)))  
{  }

Bounding::~Bounding() {
	centre.reset();
	extent_x.reset();
	extent_y.reset();
	extent_z.reset();
}

void Bounding::SetCentre(vec3 & v) {
  centre = make_shared<vec3>(v);
}

bool straddles(const pair<float, float> & a, const pair<float, float> & b) {
	return (a.first >= b.first && a.first <= b.second)
	|| (a.second >= b.first && a.second <= b.second);
}

vec3 Bounding::projectOntoAxis(const Bounding & b, enum AXIS axis) {
    float lo, hi;
    switch (axis) { // Math needs further evaluation
    case X:
	//Vector2 bx = *b.extent_x;
	//lo = projection( Point2(Vector2(*(b.centre)) + (bx * -1)), xAxis());
	//hi = projection( Point2(Vector2(*(b.centre)) + bx), xAxis());
	break;

	case Y:
	//Vector2 by = *b.extent_y;
	//lo = projection( Point2(Vector2(*(b.centre)) + (by * -1)), yAxis());
	//hi = projection( Point2(Vector2(*(b.centre)) + by), yAxis());
	break;

	case Z:
	//Vector2 by = *b.extent_y;
	//lo = projection( Point2(Vector2(*(b.centre)) + (by * -1)), zAxis());
	//hi = projection( Point2(Vector2(*(b.centre)) + by), zAxis());
	break;
    }
	
	return make_pair(lo, hi);
}

bool Bounding::CollidesWith(const shared_ptr<Bounding> b) { // Math needs further evaluation
	float a_x = *this.extent_x;
	//pair<float, float> a_y = projectOntoAxis(*this, Y);
	//pair<float, float> a_y = projectOntoAxis(*this, Z);
	//pair<float, float> b_x = projectOntoAxis(*b, X);
	//pair<float, float> b_y = projectOntoAxis(*b, Y);
	//pair<float, float> b_y = projectOntoAxis(*b, Z);
	//return (straddles(a_x_proj, b_x_proj)) && (straddles(a_y_proj, b_y_proj));
	
	
	// http://www.gamefromscratch.com/post/2012/11/26/GameDev-math-recipes-Collision-detection-using-an-axis-aligned-bounding-box.aspx 
	if(a_x <= b_x + b.width && b_x <= a_x + this.width &&
	a_y <= b_y + b.height && b_y <= a_y + this.height && 
	a_z <= b_z + b.length && b_z <= a_z + this.length)
	{
		// Need to test this!!!!
	}
	}
	return true; 
}
