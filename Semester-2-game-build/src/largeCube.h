#include "cube.h"

// http://en.cppreference.com/w/cpp/language/override

class LargeCube : Cube {
	public:
	 void vertexs() override;
	 void elements() override;
};
