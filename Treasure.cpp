#include "Item.h"

// Randomly generate Treasure
Treasure::Treasure() { value = rand() % 901 + 100; }

Treasure::~Treasure() {}

int Treasure::getCost() { return 0; }

int Treasure::getStrength() { return 0; }

ObstacleType Treasure::getObstacle() { return BOULDER; }

int Treasure::getDetails(string &source, int &y, int &x) { return 0; }

// Get money
int Treasure::getMoney() { return value; }

int Treasure::getTruth() { return 0; }

void Treasure::setClue(string clue, int y, int x) { return; }

string Treasure::getName() { return "Treasure!"; }
