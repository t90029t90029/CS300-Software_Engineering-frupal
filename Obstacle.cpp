#include "Item.h"

// Randomly generate Obstacle
Obstacle::Obstacle() {
  const int itemCount = 3;
  const int ratingCount = 3;
  const int nameCount = 3;
  const int energyMultiplier = 5;

  string names[itemCount][nameCount] = {// Rock
                                        {"Barrier", "Rock Pile", "Boulder"},
                                        // Plant
                                        {"Shrubbery", "Vines", "Tree"},
                                        // Monster
                                        {"Gremlin", "Goblin", "Orc"}};

  // The rating will determine which adjective
  string adjectives[ratingCount] = {"Weak", "Daunting", "Formidable"};

  type = ObstacleType((rand() % itemCount) + 1);
  // Obstacle's energy cost depends on its rating
  int rating = (rand() % ratingCount) + 1;
  int nameIndex = (rand() % nameCount);

  energy = rating * energyMultiplier;
  name = adjectives[rating - 1] + " " + names[type - 1][nameIndex];

  /* Test item generation
        erase();
        mvprintw(0, 0, "%s %d %d", name.c_str(), rating, type);
        getch();
  **/
}
Obstacle::~Obstacle() {}

// Get energy to remove obstacle
int Obstacle::getStrength() { return energy; }

int Obstacle::getCost() { return 0; }

ObstacleType Obstacle::getObstacle() { return type; }

int Obstacle::getDetails(string &source, int &y, int &x) { return 0; }

int Obstacle::getMoney() { return 0; }

int Obstacle::getTruth() { return 0; }

void Obstacle::setClue(string clue, int y, int x) { return; }

string Obstacle::getName() { return name; }
