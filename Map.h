#include "Tile.h"

const int WIDTH = 128;
const int HEIGHT = 128;

class Map {
  public:
    Map();
  private:
    Tile tiles[HEIGHT][WIDTH];
};