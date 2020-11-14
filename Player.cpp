#include "Player.h"
#include "Map.h"

Player::Player(): energy(100), y(0), x(0) {
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
