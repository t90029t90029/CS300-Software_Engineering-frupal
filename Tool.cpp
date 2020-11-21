#include "Item.h"

// Tool Constructor
Tool::Tool() {
  type = ToolType(rand() % 4);
  switch(type) {
    case AXE:
	    name = "Axe";
	    break;
    case HOE:
	    name = "Hoe";
	    break;
    case PICKAXE:
	    name = "Pick Axe";
	    break;
    case SHOVEL:
	    name = "Shovel";
	    break;
    default:
	    break;
  } 
}

Tool::~Tool() {
}

// Get cost of the tool
int Tool::getCost() {
  switch(type) {
    case AXE:
	    cost = 10;
	    break;
    case HOE:
	    cost = 20;
	    break;
    case PICKAXE:
	    cost = 30;
	    break;
    case SHOVEL:
	    cost = 40;
	    break;
    default:
	    break;

  }
  return cost;
}

// Return multiplyer to reduce energy needed
int Tool::getStrength() {
  switch(type) {
    case AXE:
	    rating = 2;
	    break;
    case HOE:
	    rating = 3;
	    break;
    case PICKAXE:
	    rating = 4;
	    break;
    case SHOVEL:
	    rating = 5;
	    break;
    default:
	    break;

  }
  return rating;
}

int Tool::getObstacle() {
  return 0;
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
