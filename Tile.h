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

enum ItemType {
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
    ItemType itemtype;
    int getCost(ItemType itemtype);
    int getEnergy(ItemType itemtype);
    char item;
    bool isVisible;
};
