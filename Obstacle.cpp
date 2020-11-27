#include "Item.h"

// Randomly generate Obstacle
Obstacle::Obstacle() {
  type = ObstacleType(rand()%3);
  switch(type) {
    case TREE:
	    energy = 10;
	    break;
    case BOULDER:
	    energy = 20;
	    break;
    case SOIL:
	    energy = 15;
	    break;
    default:
	    break;
  } 
}
Obstacle::~Obstacle() {
}

// Get energy to remove obstacle
int Obstacle::getStrength() {
  return energy;
}

int Obstacle::getCost() {
  return 0;
}

ObstacleType Obstacle::getObstacle() {
  return type;
}

int Obstacle::getDetails(string & source) {
  return 0;
}

int Obstacle::getMoney() {
  return 0;
}
    
int Obstacle::getTruth() {
  return 0;
}

void Obstacle::setClue(string clue){
  return;
}
