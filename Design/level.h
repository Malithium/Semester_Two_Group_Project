
#include <fstream>
// Library for file input
#include <iostream>
#include <string>

// Library to load the levels
#include <vector>

class Level  {
  public:
    void runlevel(int lvl);

  private:
    void blockpositions();
    void fillVector(int lvl);
    std::vector<float>cubepositions(); // This vector will read in the XYZ from a .(*) document with the cube positions which makes the levels easier to edit and manage.
};
