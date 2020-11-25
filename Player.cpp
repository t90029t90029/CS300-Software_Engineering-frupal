#include "Player.h"

Player::Player():
                  tools(NULL),
                  energy(100), money(1000),
                  y(0), x(0),
                  binoculars(false), ship(false) {

  tools = new Tool[MAX_INVENTORY];
}

bool Player::hasBinoculars() {
  return binoculars;
}

void Player::setBinoculars(bool value) {
  binoculars = value;
}

bool Player::hasShip() {
  return ship;
}

void Player::setShip(bool value) {
  ship = value;
}

// Dummy function
int Player::hasTool(ObstacleType type) {
  return 2;
}

Tool * Player::getTools() {
  return tools;
}

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
