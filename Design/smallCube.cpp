 static GLfloat g_colour_buffer_data[12*3*3];  // Colours of ground blocks
 
 // Vertex's for the cube
 static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f
	};

 // Connects the vertex's to make the cube 
 static const GLuint element_buffer[] = {
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

	// Will fill the colour buffer with shades of green
	for(int i = 0; i < 12*3; i++)
	{ 
		g_colour_buffer_data[3*i+0] = 0.039f;
		g_colour_buffer_data[3*i+1] = 0.186f;
		g_colour_buffer_data[3*i+2] = 0.059f;		
	};