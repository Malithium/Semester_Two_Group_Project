#ifndef LEVEL_H
#define LEVEL_H
#define GLM_FORCE_RADIANS

// Libraries for file input
#include <fstream>
#include <iostream>
// Library to store the cube positions
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <src/gameAssetManager.h>
#include <src/diamondAsset.h>
#include <src/CubeAsset.h>
#include <src/DoorAsset.h>

#include <src/boundingBox.h>
#include <src/camera.h>
#include <src/events.h>

/**
* This class runs the inner loop for all the individual levels, which means
* receiving inputs, checking collision, drawing the cubes. It is also 
* responsible reading cube positions, from the .json files and then passing
* them to the gameassetmanager to manipulate them. 
*/

class Level  {
  public:
    bool runLevel(int lvl, SDL_Window* window);
    int blockPositions();
    bool fillVector(int lvl);
    bool collisionDetection(int lvl);
    void sky();

  private:
    Camera player;
    bool running; 
	bool decrease = false;
    float r = 0;
	float g = 0;
	float b = 0;
    int cubes, diamonds;
    std::vector<float> cubepositions; // This vector will read in the XYZ from a .json document with the cube positions which makes the levels easier to edit and manage.
    std::shared_ptr<GameAssetManager> asset_manager;
	std::shared_ptr<Bounding> Pbbox;
};

#endif //LEVEL_H
