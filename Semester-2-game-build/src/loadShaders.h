#pragma once

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class loadShaders
{

public:
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
private:
	// Create the shaders
	GLuint VertexShaderID;
	GLuint FragmentShaderID;

	std::string VertexShaderCode;
	std::string FragmentShaderCode;
	
	GLint Result = GL_FALSE;
	int InfoLogLength;

};

