#include "Item.h"

// Randomly generate Obstacle
Obstacle::Obstacle() {
  type = ObstacleType((rand() % 4) + 1);
	string obstacleNames[4][3] = {
      // Rock
			{
        "Gravel",
        "Rock Pile",
        "Boulder"
      },
      // Plant
      {
        "Tall Grass",
        "Vines",
        "Tree"
      },
      // Ground
      {
        "Mud",
        "Sinkhole",
        "Quicksand"
      },
      // Monster
      {
        "Gremlin",
        "Goblin",
        "Orc"
      }
	};

	// Choose a random obstacle type and strength
	int rating = (rand() % 3) + 1;
	energy = (rating+1) * 5;
	name = obstacleNames[type - 1][rating - 1];

	/* Test item generation
	erase();
	mvprintw(0, 0, "%s %d %d", name.c_str(), rating+1, energy);
	getch();
  */
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
