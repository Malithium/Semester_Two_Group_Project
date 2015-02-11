 static GLfloat g_colour_buffer_data[12*3*3];  // Colours of ground blocks
 
 // Vertex's for the cube
 static const GLfloat g_vertex_buffer_data[] = { 
		 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.0f,  0.0f,  0.0f,
	};

 // Connects the vertex's to make the cube 
 static const GLuint element_buffer[] = {
		1, 0, 2,
		2, 5, 1,
		2, 0, 3,
		3, 5, 2,
		3, 0, 4,
		4, 5, 3,
		4, 0, 1,
		1, 5, 4,
};

	// Will fill the colour buffer with shades of (light blue?)
	for(int i = 0; i < 12*3; i++)
	{ 
		g_colour_buffer_data[3*i+0] = 0.039f;
		g_colour_buffer_data[3*i+1] = 0.186f;
		g_colour_buffer_data[3*i+2] = 0.059f;		
	};