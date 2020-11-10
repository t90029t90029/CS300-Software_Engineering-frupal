enum TileType {
  MEADOW, 
  WATER, 
  SWAMP, 
  WALL, 
  DIAMOND
};

class Tile {
  public:
    Tile(); 
    TileType type;
		char item;
};
