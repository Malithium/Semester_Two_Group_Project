
// Libraries for file input
#include <fstream>
#include <iostream>
// Library to store the cube positions
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cube.h"
#include "largeCube.h"
#include "mediumCube.h"
#include "smallCube.h"

class Level  {
  public:
    void runLevel(int lvl);

  private:
    void blockPositions();
    bool fillVector(int lvl);
    std::vector<float> cubepositions; // This vector will read in the XYZ from a .(*) document with the cube positions which makes the levels easier to edit and manage.
};
