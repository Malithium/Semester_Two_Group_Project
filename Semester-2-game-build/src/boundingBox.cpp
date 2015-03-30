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

bool straddles(const pair<float, float> & a, const pair<float, float> & b) {
	return (a.first >= b.first && a.first <= b.second)
	|| (a.second >= b.first && a.second <= b.second);
}

vec3 Bounding::projectOntoAxis(const Bounding & b, enum AXIS axis) {
     float lo, mi, hi;
     switch (axis) // Math needs further evaluation
     {
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
	//lo = projection( Point2(Vector2(*(b.centre)) + (by * -1)), yAxis());
	//hi = projection( Point2(Vector2(*(b.centre)) + by), yAxis());
	break;
     }
	return vec3(lo, mi, hi);
}

bool Bounding::CollidesWith(const shared_ptr<Bounding> b) { // Math needs further evaluation
	//pair<float, float> a_x_proj = projectOntoAxis(*this, b.X);
	//pair<float, float> a_y_proj = projectOntoAxis(*this, b.Y);
	//pair<float, float> b_x_proj = projectOntoAxis(*b, b.X);
	//pair<float, float> b_y_proj = projectOntoAxis(*b, b.Y);
	//return (straddles(a_x_proj, b_x_proj)) && (straddles(a_y_proj, b_y_proj));
	return true; 
}