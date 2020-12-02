#include "Item.h"

// Randomly generate Ship
Ship::Ship(){
  value = rand() % 901 + 100;
}

Ship::~Ship(){
}

int Ship::getCost(){
  return value;
}

int Ship::getStrength(){
  return 0;
}

ObstacleType Ship::getObstacle(){
  return BOULDER;
}

int Ship::getDetails(string & source){
  return 0;
}

// Get money
int Ship::getMoney(){
  return 0;
}

int Ship::getTruth(){
  return 0;
}

void Ship::setClue(string clue){
  return;
}
