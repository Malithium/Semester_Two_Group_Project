#include <largeCube.h>

void LargeCube::vertexs()
{
	vertex_buffer[] = { 
	-3.0f, -1.0f,  3.0f,
	 3.0f, -1.0f,  3.0f,
	 3.0f,  1.0f,  3.0f,
	-3.0f,  1.0f,  3.0f,
	-3.0f, -1.0f, -3.0f,
	 3.0f, -1.0f, -3.0f,
	 3.0f,  1.0f, -3.0f,
	-3.0f,  1.0f, -3.0f
	};
}

void LargeCube::elements()
{
	element_buffer[] = {
		0, 1, 2,
		2, 3, 0,
		3, 2, 6,
		6, 7, 3,
		7, 6, 5,
		5, 4, 7,
		4, 5, 1,
		1, 0, 4,
		4, 0, 3,
		3, 7, 4,
		1, 5, 6,
		6, 2, 1
	};
}