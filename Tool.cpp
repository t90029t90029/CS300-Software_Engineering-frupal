#include "Item.h"
#include <string>

using namespace std;

// Tool Constructor
Tool::Tool() {
  int itemCount = 3;
  int ratingCount = 4;
  int nameCount = 3;
  int costMultiplier = 50;

	string names[itemCount][nameCount] = {
		// Boulder
		{
			"Hammer",
			"Pickaxe",
			"Chisel"
		},
		// Tree
		{
			"Hatchet",
			"Axe",
			"Saw"
		},
		// Monster
		{
			"Spear",
			"Sword",
			"Bow"
		}
	};

	// The rating will determine which adjective
  string adjectives[ratingCount] = {
    "Wooden",
    "Rusty",
    "Tempered",
    "Magic"
  };

	int nameIndex = rand() % nameCount;

  // Tool cost depends on it's rating
  obstacleType = ObstacleType((rand() % itemCount) + 1);
	rating = (rand() % ratingCount) + 1;
	cost = rating * costMultiplier;
	name = adjectives[rating - 1] + " " + names[obstacleType-1][nameIndex];

	/* Test item generation
	erase();
	mvprintw(0, 0, "%s %d %d", name.c_str(), rating, obstacleType);
	getch();
	*/
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

int Tool::getDetails(string & source,int & y,int & x) {
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

void Tool::setClue(string clue,int y,int x){
  return;
}

string Tool::getName(){
	return name;
}
