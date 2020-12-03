#include "Item.h"

// Randomly generate Food
Food::Food() {
  const int tierCount = 3;
  const int ratingCount = 3;
  const int nameCount = 3;
  const int costMultiplier = 40;
  const float energyMultiplier = 0.25;

	string names[tierCount][nameCount] = {
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
  string adjectives[ratingCount] = {
    "Stale",
    "Fresh",
    "Vital"
  };

	int rating = (rand() % ratingCount);
  int nameIndex = (rand() % nameCount);
  int foodTier = (rand() % tierCount);

  // Food energy and cost scales depending on its tier and its rating
	cost = (foodTier + 1) * (rating + 1) * costMultiplier;
  energy = cost * energyMultiplier;
	name = adjectives[rating] + " " + names[foodTier][nameIndex];

  /** Test item generation
	erase();
	mvprintw(0, 0, "%s %d %d %d", name.c_str(), rating+1, cost, energy);
	getch();
  **/
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
