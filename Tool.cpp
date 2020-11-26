#include "Item.h"

// Tool Constructor
Tool::Tool() {
  type = ToolType(rand()%4);
  switch(type) {
    case AXE:
	    name = "Axe";
	    cost = 10;
	    obstacleType = TREE;
	    rating = 2;
	    break;
    case HOE:
	    name = "Hoe";
	    cost = 20;
	    obstacleType = SOIL;
	    rating =3;
	    break;
    case PICKAXE:
	    name = "Pick Axe";
	    cost = 30;
	    obstacleType = BOULDER;
	    rating =4;
	    break;
    case SHOVEL:
	    name = "Shovel";
	    cost = 40;
	    obstacleType = SOIL;
	    rating =5;
	    break;
    default:
	    break;
  } 
}

Tool::~Tool() {
}

// Get cost of the tool
int Tool::getCost() {
    return cost;
}

// Return multiplyer to reduce energy needed
int Tool::getStrength() {
    return rating;
}

ObstacleType Tool::getObstacle() {
  return obstacleType;
}

int Tool::getDetails(string & source) {
  if(name.length() > 0){
    source = name;
    return 1;
  }
  return 0;
}

int Tool::getMoney() {
  return 0;
}

int Tool::getTruth() {
  return 0;
}

void Tool::setClue(string clue){
  return;
}

int Tool::getToggle(){
  return 0;
}
string Tool::getName(){
	return name;
}
