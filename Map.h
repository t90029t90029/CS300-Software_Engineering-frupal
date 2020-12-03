#pragma once

#include "Tile.h"
#include<ncurses.h>
#include<string>
#include<fstream>
#include<iostream>

const int WIDTH = 128;
const int HEIGHT = 128;
const int MIN_WIDTH = 80;
const int MIN_HEIGHT = 24;

class Map {
  public:
    Map();
    ~Map();
    void display(int playerY, int playerX, bool hasBinoculars);
    void load(int & playerStartY, int & playerStartX);
    bool isPurchasable(int y, int x);
    void highlightItem(int y, int x);
    Tile *getTile(int y, int x);
    void viewportSize(void);
  private:
    Tile ** tiles;

    // Viewport
    int shiftX, shiftY; // Amount screen shifted from edge of map
    int wView, hView;   // Width and height to display
};

