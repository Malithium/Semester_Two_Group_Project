#include "boundingBox.h"

Bounding::Bounding(const vec3 centre, const float w, const float h, const float l) 
{ 
	pos = centre;
	width = w;
	height = h;
	length = l;
}

Bounding::~Bounding() {
}

void Bounding::SetCentre(vec3 v) {
  
  pos = v;
}

float Bounding::getWidth()
{
	return width;
}

float Bounding::getHeight()
{
	return height;
}

float Bounding::getLength()
{
	return length;
}


bool Bounding::CollidesWith(const shared_ptr<Bounding> b) {	
	float a_x = this->pos.x;
	float b_x = b->pos.x;
	float a_y = this->pos.y;
	float b_y = b->pos.y;
	float a_z = this->pos.z;
	float b_z = b->pos.z;

	// http://www.gamefromscratch.com/post/2012/11/26/GameDev-math-recipes-Collision-detection-using-an-axis-aligned-bounding-box.aspx 

	if(a_x <= (b_x + b->getWidth() ) && b_x <= (a_x + this->getWidth() ) &&
	a_y <= (b_y + b->getHeight() ) && b_y <= (a_y + this->getHeight() ) && 
	a_z <= (b_z + b->getLength() ) && b_z <= (a_z + this->getLength() ) )
	{	
		return true;
	}

	return false; 
}
