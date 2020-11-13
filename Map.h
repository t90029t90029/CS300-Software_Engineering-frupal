#include "Tile.h"
#include "Player.h"
#include<ncurses.h>

const int WIDTH = 128;
const int HEIGHT = 128;

class Map {
  public:
    Map();
    void displayMap();
  private:
    Tile tiles[HEIGHT][WIDTH];
};

