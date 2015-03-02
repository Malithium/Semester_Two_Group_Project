
#include <fstream>
// Library for file input
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Library to load the levels
#include <vector>

class Level  {
  public:
    void runLevel(int lvl);

  private:
    void blockPositions();
    bool fillVector(int lvl);
    std::vector<float> cubepositions; // This vector will read in the XYZ from a .(*) document with the cube positions which makes the levels easier to edit and manage.
};
