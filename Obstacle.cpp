#include "Item.h"

// Randomly generate Obstacle
Obstacle::Obstacle() {
  type = ObstacleType((rand() % 4) + 1);
	string names[4][3] = {
      // Rock
			{
        "Barrier",
        "Rock Pile",
        "Boulder"
      },
      // Plant
      {
        "Bush",
        "Vines",
        "Tree"
      },
      // Ground
      {
        "Terrain",
        "Mud",
        "Quicksand"
      },
      // Monster
      {
        "Gremlin",
        "Goblin",
        "Orc"
      }
	};

  // The rating will determine which adjective
  string adjectives[3] = {
    "Burdensome",
    "Formidable",
    "Fearsome"
  };

	// Choose a random obstacle type and strength
	int rating = (rand() % 3) + 1;
	energy = (rating+1) * 5;
	name = adjectives[rating - 1] + " " + names[type - 1][rating - 1];

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
