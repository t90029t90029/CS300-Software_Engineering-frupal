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
		char item;
};
