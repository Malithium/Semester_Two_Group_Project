#include "gameAssetManager.h"

/**
* Creates a GameAssetManager to load the correct shaders based on the
* ApplicationMode.
*/

GameAssetManager::GameAssetManager() {

	loadShaders shader;
	// Create and compile our GLSL program from the shaders
	programID = shader.LoadShaders("shaders/vertex.vs", "shaders/FragmentShader.fragmentshader");
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
* Draws each GameAsset in the scene graph.
*/

void GameAssetManager::Draw() {
	for(auto ga: draw_list) {
		ga->Draw(programID);
	}
}
