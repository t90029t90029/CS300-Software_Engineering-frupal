#include "Item.h"

// Randomly generate Food
Food::Food(){
  type = FoodType(rand() % 3);
  switch(type) {
    case CRACKER:
	    energy = 20;
	    cost = 50;
	    break;
    case STEAK:
	    energy = 100;
	    cost = 200;
	    break;
    case SPRITE:
	    energy = 30;
	    cost = 80;
	    break;
    default:
	    break;
  } 
}

Food::~Food(){
}

// pay for the food
int Food::getCost(){
  return cost;
}

// Restore energy
int Food::getStrength(){
  return energy;
}

int Food::getObstacle(){
  return 0;
}

int Food::getDetails(string & source){
  return 0;
}

int Food::getMoney(){
  return 0;
}

int Food::getTruth(){
  return 0;
}

void Food::setClue(string clue){
  return;
}

int Food::getToggle(){
  return 0;
}
