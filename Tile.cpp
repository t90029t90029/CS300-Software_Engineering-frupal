#include "Tile.h"

Tile::Tile(): type(MEADOW), item(' ') , isVisible(false), itemType(NULL){
#ifdef NOFOG
  isVisible = true;
#endif // NOFOG
}

string Tile::enumToString(TileType type){
  switch(type){
    case EMPTY:
      return "EMPTY";

    case MEADOW:
      return "MEADOW";

    case WATER:
      return "WATER";

    case SWAMP:
      return "SWAMP";

    case WALL:
      return "WALL";

    case DIAMOND:
      return "Royal Diamond";

    case PLAYER:
      return "PLAYER";

    default:
      return " ";
  }
}

