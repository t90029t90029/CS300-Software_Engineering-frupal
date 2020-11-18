#pragma once

#include "Tile.h"
#include<ncurses.h>
#include<string>
#include<fstream>
#include<iostream>

const int WIDTH = 128;
const int HEIGHT = 128;

class Map {
  public:
    Map();
    ~Map();
    void display(int playerX, int playerY);
    void load();
    Tile *getTile(int y, int x);
  private:
    Tile ** tiles;
};

