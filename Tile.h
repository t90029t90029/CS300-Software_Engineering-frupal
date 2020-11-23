#pragma once

#include "Item.h"

enum TileType {
  EMPTY,
  MEADOW,
  WATER,
  SWAMP,
  WALL,
  DIAMOND,
  PLAYER
};

class Tile {
  public:
    Tile();
    TileType type;
    string enumToString(TileType);
    char item;
    bool isVisible;
    Item *itemType;
};
