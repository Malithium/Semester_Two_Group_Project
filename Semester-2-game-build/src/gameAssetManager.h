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
#include <src/camera.h>
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
	 // The main methods needed to create and run the world
	 void AddAsset(std::shared_ptr<GameAsset>);
	 void Draw();
	 void Move(int num, glm::vec3 pos);
	 
	 // Additional methods designed to help add functionality to the program
	 bool Collision(int n1, const shared_ptr<Bounding> b);
	 void Clear();
	 void Intelligence(int cubes, int diamonds);
	 void Remove(int num);
	 int Size();
	private:
	 GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	 // The internal scene graph is a simple list.
	 std::vector<std::shared_ptr<GameAsset>> draw_list;
	 GLuint programID;
	 Camera player;
};

#endif // GAMEASSETMANAGER_H
