#include "Item.h"

// Randomly generate Food
Food::Food() {
  type = FoodType((rand() % 3) + 1);
	// 3 food types, 3 strengths per type
	string foodNames[3][3] = {
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

	// Choose a random food type and strength
	int rating = (rand() % 3) + 1;

  // Food types stack, meaning the more the rating the more the cost/restoration
	cost = (type + 1) * rating * 15;
  energy = cost / 2;
	name = foodNames[type - 1][rating - 1];

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
