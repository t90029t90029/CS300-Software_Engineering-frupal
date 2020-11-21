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

enum FoodType {
  CRACKER,
  STEAK,
  SPRITE,
  NON
};

class Tile {
  public:
    Tile();
    TileType type;
    char item;
    Item *itemType1;
    FoodType itemtype;
    int getCost(FoodType itemtype);
    int getEnergy(FoodType itemtype);
    bool isVisible;
};
