#include "Player.h"
#include <sstream>

Player::Player():
                  toolCount(0),
                  binoculars(false), ship(false),
		  clueY(0), clueX(0), clue(false), seeClue(true),
                  energy(100), money(1000),
                  y(0), x(0) {

  // Initialize inventory
  for (int i = 0; i < MAX_INVENTORY; ++i)
    tools[i] = NULL;
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

bool Player::hasClue(int & y,int & x) {
  if(clue){
    y = clueY;
    x = clueX;
  }
  return clue;
}

void Player::setClue(bool value,int y,int x) {
  if(value){
    clueY = y;
    clueX = x;
    clue = value;
  }
}

bool Player::wantSeeClue() {
  return seeClue;
}

void Player::setSeeClue(bool value) {
  seeClue = value;
}

string Player::itemDirect(bool truth,int itemY,int itemX) {
  std::ostringstream output;
  string direct;

  //truth
  if(truth){
    if(itemY >= y){
      output << itemY-y;
      direct = output.str() +" grovniks to the south";
    }
    else{
      output << y-itemY;
      direct = output.str() +" grovniks to the north";
    }
    //clear the buffer
    output.str("");
    output.clear();

    direct += " and ";
    if(itemX >= x){
      output << itemX-x;
      direct += output.str() +" grovniks to the east.";
    }
    else{
      output << x-itemX;
      direct += output.str() +" grovniks to the west.";
    }
  }

  //lie -- reverse
  else{
    if(itemX >= x){
      output << itemX-x;
      direct = output.str() +" grovniks to the south";
    }
    else{
      output << x-itemX;
      direct = output.str() +" grovniks to the north";
    }
    //clear the buffer
    output.str("");
    output.clear();

    direct += " and ";
    if(itemY >= y){
      output << itemY-y;
      direct += output.str() +" grovniks to the east.";
    }
    else{
      output << y-itemY;
      direct += output.str() +" grovniks to the west.";
    }
  }
  return direct;
}

vector<Tool*> Player::hasTool(Item *item) {
	vector<Tool*> toolsCanUse;
	Obstacle * obstacle = dynamic_cast<Obstacle *>(item);
	for(int i = 0; i<toolCount; i++) {
		if(tools[i]->getObstacle() == obstacle->getObstacle()) {
			toolsCanUse.push_back(tools[i]);
		}
	}
	return toolsCanUse;
}

bool Player::addTool(Item * item) {
   // Downcast item to tool
   Tool * tool = dynamic_cast<Tool *>(item);

   // Somehow we go an item that isn't a tool
   if (tool == NULL)
    return false;

   // Inventory is full
   if (toolCount >= MAX_INVENTORY)
      return false;

   tools[toolCount++] = tool;
   return true;
}
bool Player::removeTool(Tool* item) {

   int i;
   for(i =0;i < toolCount; i++) {
	   if(tools[i]->getName() == item->getName())
	   break;
   }
   toolCount--;
   for(int j=i; j<toolCount;j++)
	   tools[j] = tools[j+1];
   return true;
}


Tool ** Player::getTools() {
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
int Player::getNumberOfTool() {
	return toolCount;
}
