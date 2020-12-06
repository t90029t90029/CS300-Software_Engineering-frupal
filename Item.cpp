#include "Item.h"

void Item::setType(int i) {
  if(i == 0)
    type = SHIP;
  else if(i == 1)
    type = BINOCULARS;
  else if(i == 2)
    type = TOOLS;
  else if(i == 3)
    type = FOOD;
  else if(i == 4)
    type = OBSTACLES;
  else if(i == 5)
    type = CLUE;
  else if(i == 6)
    type = TREASURE;
}

ItemType Item::getType() {
  return type;
}

string Item::enumToString() {
  switch(type){
    case SHIP:
      return "ship";

    case BINOCULARS:
      return "binoculars";

    case TOOLS:
      return "tool";

    case FOOD:
      return "food";

    case OBSTACLES:
      return "obstacle";

    case CLUE:
      return "clue";

    case TREASURE:
      return "treasure chest";

    default:
      return " ";
  }
}
