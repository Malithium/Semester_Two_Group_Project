#ifndef GAMEASSETMANAGER_H
#define GAMEASSETMANAGER_H
#define GLM_FORCE_RADIANS

#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <src/boundingBox.h>
#include <src/gameAsset.h>

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
	 void Remove(int num);
	 bool Collision(int n1, const shared_ptr<Bounding> b);
	 void Draw();
	 void Clear();
	  int Size();
	 GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	private:
	 // The internal scene graph is a simple list.
	 std::vector<std::shared_ptr<GameAsset>> draw_list;
	 GLuint programID;
};

#endif // GAMEASSETMANAGER_H
