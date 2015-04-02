#include "gameAssetManager.h"

/**
* Creates a GameAssetManager to load the correct shaders based on the
* ApplicationMode.
*/

GameAssetManager::GameAssetManager() {
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("shaders/vertex.vs", "shaders/fragment.fs");
}

/**
* Deletes a GameAssetManager, in particular it will clean up any modifications
* to the OpenGL state.
*/

GameAssetManager::~GameAssetManager() {
	glDeleteProgram(programID);
}

/**
* Adds a GameAsset to the scene graph.
*/

void GameAssetManager::AddAsset(std::shared_ptr<GameAsset> the_asset) {
	draw_list.push_back(the_asset);
}

/**
* Changes the vec3 of an asset, transitioning it
*/
void GameAssetManager::Move(int num, glm::vec3 pos) {
    draw_list.at(num)->NewPosition(pos);
}

void GameAssetManager::Remove(int num) {
    draw_list.erase(draw_list.begin() + num); // Removes an object from vector
}

bool GameAssetManager::Collision(int n1, const shared_ptr<Bounding> b) {
    return draw_list.at(n1)->Collides(b);
}

/**
* Draws each GameAsset in the scene graph.
*/
void GameAssetManager::Draw() {
	for(auto ga: draw_list) {
		ga->Draw(programID);
	} 
}

/**
* Empties the draw vector, allowing for the next levels cubes to load
*/
void GameAssetManager::Clear() {
	draw_list.clear();
}

int GameAssetManager::Size()  {
	return (draw_list.size()-1);
}


/**
* Reads in the shaders, to produce a ProgramID which points to the linked location
*/
GLuint GameAssetManager::LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::string FragmentShaderCode;
	
	/// Read the Vertex Shader code from the file
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	/// Read the Fragment Shader code from the file
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	/// Compile Vertex Shader
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	/// Compile Fragment Shader
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	/// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
