#include "Player.h"

Player::Player(): tools(NULL), energy(100), money(0), y(0), x(0) {
  tools = new Tool[MAX_INVENTORY];
}

/** Dummy functions, to be replaced **/
bool Player::hasBinoculars() {
  return true;
}

bool Player::hasShip() {
  return true;
}

int Player::hasTool(ObstacleType type) {
  return 2;
}

Tool * Player::getTools() {
  return tools;
}
/** **/

void Player::move(int y, int x) {
  this->y = y;
  this->x = x;
}

bool Player::isAlive() {
  return (energy > 0);
}

void Player::locate(int & y, int & x)
{
  y = this->y;
  x = this->x;
}

int Player::getEnergy() {
  return energy;
}

void Player::setEnergy(int value) {
  if (value < 0)
    energy = 0;
  else
    energy = value;
}

int Player::getMoney() {
  return money;
}

void Player::setMoney(int value) {
  if (value < 0)
    money = 0;
  else
    money = value;
}


void Player::setStartLocation(int playerStartY, int playerStartX)
{
    this->y = playerStartY;
    this->x = playerStartX;
}
