#include "Item.h"

// Randomly generate Food
Food::Food() {
  type = FoodType((rand() % 3) + 1);
	// 3 food tiers each with 3 food names
	string names[3][3] = {
      // Snack
			{
        "Berries",
        "Nuts",
        "Crackers"
      },
      // Meal
      {
        "Beans",
        "Bread",
        "Porridge"
      },
      // Feast
      {
        "Hog",
        "Venison",
        "Steak"
      }
	};

  // The rating will determine which adjective
  string adjectives[3] = {
    "Stale",
    "Fresh",
    "Vital"
  };

	// Random rating
	int rating = (rand() % 3) + 1;

  // Random food name
  int index = (rand() % 3);

  // Food types stack, meaning the more the rating the more the cost/restoration
	cost = (type + 1) * rating * 15;
  energy = cost / 2;
	name = adjectives[rating - 1] + " " + names[type - 1][index];

  /* Test item generation
	erase();
	mvprintw(0, 0, "%s %d %d %d", name.c_str(), rating+1, cost, energy);
	getch();
  */
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

ObstacleType Food::getObstacle(){
  return BOULDER;
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

string Food::getName(){
	return name;
}
