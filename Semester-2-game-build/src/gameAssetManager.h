#ifndef GAMEASSETMANAGER_H
#define GAMEASSETMANAGER_H
#define GLM_FORCE_RADIANS

#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <src/loadShaders.h>
#include <GL/gl.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gameAsset.h"

/**
* GameAssetManager is a container for GameAssets. It also provides utility
* functions to to create a simple OpenGL program that can be used to draw a
* simple GameAsset.
*/

class GameAssetManager {
	public:
	 GameAssetManager();
	 ~GameAssetManager();
	 void AddAsset(std::shared_ptr<GameAsset>);
	 void Move(int num, glm::vec3 pos);
	 void Draw();
	 void Clear();
	private:
	 // The internal scene graph is a simple list.
	 std::vector<std::shared_ptr<GameAsset>> draw_list;
	 GLuint programID;
};

#endif // GAMEASSETMANAGER_H
