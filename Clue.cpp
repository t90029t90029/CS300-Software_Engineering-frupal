#include "Item.h"

// Randomly generate Clue
Clue::Clue() {
  type = ClueType(rand() % 2);
  switch (type) {
  case TRUTH:
    isTrue = "TRUTH";
    break;
  case LIE:
    isTrue = "LIE";
    break;
  default:
    break;
  }
}

Clue::~Clue() { content.clear(); }

int Clue::getCost() { return 0; }

int Clue::getStrength() { return 0; }

ObstacleType Clue::getObstacle() { return BOULDER; }

// Get hint
int Clue::getDetails(string &source, int &y, int &x) {
  if (content.length() > 0) {
    source = content;
    y = targetY;
    x = targetX;
    return 1;
  }
  return 0;
}

int Clue::getMoney() { return 0; }

// Get true/lie
int Clue::getTruth() {
  if (type == TRUTH)
    return 1;
  return 0;
}

// Set hint
void Clue::setClue(string clue, int y, int x) {
  content = clue;
  targetY = y;
  targetX = x;
}

string Clue::getName() { return "Clue"; }
