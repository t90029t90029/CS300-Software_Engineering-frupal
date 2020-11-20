#include "Item.h"

// Randomly generate Obstacle
Obstacle::Obstacle() {
  type = ObstacleType(rand() % 2);
  switch(type) {
    case TREE:
	    energy = 10;
	    break;
    case BOULDER:
	    energy = 20;
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

int Obstacle::getObstacle() {
  return 0;
}
int Obstacle::getDetails() {
  return 0;
}






