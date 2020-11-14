#include "Tile.h"
#include<ncurses.h>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
const int WIDTH = 128;
const int HEIGHT = 128;

class Map {
  public:
    Map();
    void displayMap();
    void loader();
  private:
    Tile tiles[HEIGHT][WIDTH];
};

