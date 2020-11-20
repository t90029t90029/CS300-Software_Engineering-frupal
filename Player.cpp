#include "Player.h"
#include "Map.h"

using namespace std;

Player::Player(): energy(100), money(0), y(0), x(0){
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

