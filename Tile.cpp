#include "Tile.h"

Tile::Tile(): type(MEADOW), item(' ') {

}

int Tile::getCost(ItemType itemtype){
  if(itemtype == CRACKER)
    return 50;
  else if(itemtype == STEAK)
    return 200;
  else if(itemtype == SPRITE)
    return 80;

  return 0;	//no match
}
 
int Tile::getEnergy(ItemType itemtype){
  if(itemtype == CRACKER)
    return 20;
  else if(itemtype == STEAK)
    return 100;
  else if(itemtype == SPRITE)
    return 30;

  return 0;	//no match
}



