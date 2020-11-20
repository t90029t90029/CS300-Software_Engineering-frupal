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
    FoodType food;
    char item;
};
