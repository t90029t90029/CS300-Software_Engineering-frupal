#include "Item.h"
#include <string>

using namespace std;

// Tool Constructor
Tool::Tool() {
	// 5 obstacle types, 3 names for each
	string names[5][3] = {
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
		// Soil
		{
			"Rake",
			"Shovel",
			"Hoe",
		},
		// Monster
		{
			"Spear",
			"Sword",
			"Bow"
		}
	};

	// The rating will determine which adjective
  string adjectives[3] = {
    "Rusty",
    "Silver",
    "Enchanted"
  };

	// Which name to pick
	int index = rand() % 3;

	// Choose a random obstacle type and strength
  obstacleType = ObstacleType((rand() % 4) + 1);
	rating = (rand() % 3) + 1;
	cost = rating * 50;
	name = adjectives[rating-1] + " " + names[obstacleType-1][index];

	/* Test item generation
	erase();
	mvprintw(0, 0, "%s %d %d", name.c_str(), rating+1, cost);
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

string Tool::getName(){
	return name;
}
