#include "Item.h"

// Randomly generate Treasure
Treasure::Treasure(){
  value = rand() % 901 + 100;
}

Treasure::~Treasure(){
}

int Treasure::getCost(){
  return 0;
}

int Treasure::getStrength(){
  return 0;
}

ObstacleType Treasure::getObstacle(){
  return BOULDER;
}

int Treasure::getDetails(string & source){
  return 0;
}

// Get money
int Treasure::getMoney(){
  return value;
}

int Treasure::getTruth(){
  return 0;
}

void Treasure::setClue(string clue){
  return;
}

int Treasure::getToggle(){
  return 0;
}
