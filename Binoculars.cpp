#include "Item.h"

// Randomly generate Binoculars
Binoculars::Binoculars(){
  value = rand() % 901 + 100;
}

Binoculars::~Binoculars(){
}

int Binoculars::getCost(){
  return value;
}

int Binoculars::getStrength(){
  return 0;
}

ObstacleType Binoculars::getObstacle(){
  return BOULDER;
}

int Binoculars::getDetails(string & source){
  return 0;
}

// Get money
int Binoculars::getMoney(){
  return 0;
}

int Binoculars::getTruth(){
  return 0;
}

void Binoculars::setClue(string clue){
  return;
}

int Binoculars::getToggle(){
  return 0;
}
