#include "Menu.h"
#include <string>
#include <cstring>
using namespace std;

void Menu::init(Map * m, Player * p) {
  this->line = 0; // This determines which line to print on
  this->showInventory = true;
  this->map = m;
  this->player = p;
}

void Menu::display() {
  // Reset line position
  this->line = 0;

  // Determine where we're printing
  MENU_X = WIDTH + 1;
  if (COLS - MENU_X < MENU_WIDTH) {
    MENU_X = COLS - MENU_WIDTH;
  }

  TEXT_X = MENU_X + 2;

  // Clear the menu
  clear();

  // Draw the border
  mvvline(0, MENU_X, MENU_BORDER, LINES);

  // Get tile at player's location
  int x, y;
  player->locate(y, x);

  // Display tile info
  displayTile(y, x);

  // Display options for current tile
  displayOptions(y, x);

  // Display the clue if there is a clue
  displayClue();

  // Display player inventory, opens with key: I
  if(showInventory)
	  displayInventory();
  // Display player stats at the bottom
  int energy = player->getEnergy();
  int money = player->getMoney();

  mvprintw(LINES - 3, TEXT_X, "Whiffles: %d", money);
  mvprintw(LINES - 2, TEXT_X, "Energy: %d", energy);
}

void Menu::clear() {
  for (int i = 0; i < LINES; ++i) {
    move(i, MENU_X);
    clrtoeol(); // Clear to end of line
  }
}

void Menu::displayTile(int y, int x) {
  //Examine tile at player's position
  Tile * tile = map->getTile(y, x);
  char itemChar = tile->item;
  Item * item = tile->itemType;
  string floor = " ";
  //Pretty'ing the names of the tiles
  switch(tile->type){
	case 1:
	   floor= "Meadows";
	   break;
	case 2:
	   floor = "Water";
	   break;
	case 3:
	   floor = "Swamp";
	   break;
	case 5:
	   floor = "*+*+Diamond+*+*";
	   break;
	default:
	   break;
  }
  mvprintw(++this->line, TEXT_X, "> Grovnik: %s", floor.c_str());
  //int nameLen = strlen(item->getName().c_str());
  

  if (item != NULL) { 
    mvprintw(++this->line, TEXT_X, "> Item:" );
    mvprintw(++this->line, TEXT_X, "> %s ", item->getName().c_str() );
    //treasure does not work as expected, substitute detectoin method used
    if(0<item->getMoney() )
        mvprintw(++this->line, TEXT_X, "> Fortune: %d", item->getMoney());
    else
	mvprintw(++this->line, TEXT_X, "> Cost: %d", item->getCost());

    if(itemChar == 'T' || itemChar == '!')//Tool or Obstacle
	mvprintw(++this->line, TEXT_X, "> Strength: %d", item->getStrength());
    else if(itemChar == 'B' || itemChar == 'S' || itemChar == '$')
	    ++this->line;
    else
	mvprintw(++this->line, TEXT_X, "> Energy: %d", item->getStrength());
  }else{ //tiles energy use
	  this->line+=4;//keeping menu spacing consistent
	  int enCost = -1;
	if(tile->type == SWAMP)
		--enCost;
	else if(tile->type == WATER)
		++enCost;
    	mvprintw(this->line, TEXT_X, "> Energy: %d", enCost);
  }

  ++this->line; // Add separation line
}

void Menu::displayOptions(int y, int x) {
  string direction;  // Direction text

  mvprintw(++this->line, TEXT_X, "Options:"); // Option heading

  // Check tiles neighboring player's position
  for (int i = 0; i < 4; ++i) {
    int _y = y, _x = x;

    switch (i) {
    case 0:
      direction = "Up)    North";
      --_y;
      break;
    case 1:
      direction = "Left)  West";
      --_x;
      break;
    case 2:
      direction = "Right) East";
      ++_x;
      break;
    case 3:
      direction = "Down)  South";
      ++_y;
      break;
    }

    // If the neigboring tile is passable, display the option to move
    Tile * tile = map->getTile(_y, _x);
    if (tile != NULL) {
      if (tile->type == MEADOW || tile->type == SWAMP) {
        mvprintw(++this->line, TEXT_X, direction.c_str());
      }
    }
  }

  // If item is purchasable, display option to buy
  if (map->isPurchasable(y, x)) {
    ++this->line;

    Tile * tile = map->getTile(y, x);
    if (player->getMoney() <= tile->itemType->getCost()) {
      mvprintw(++this->line, TEXT_X, "This is too expensive");
    }
    else {
      mvprintw(++this->line, TEXT_X, "Enter) Buy");
    }
  }
}

void Menu::displayClue(void){
  int y;
  int x;
  string clue;
  string piece;
  Tile * tile;
  long unsigned int i = 0;

  if(player->hasClue(y,x)){
    tile = map->getTile(y, x);
    this->line += 2;
    mvprintw(this->line, TEXT_X,"Clue :");
    if(tile->itemType->getDetails(clue)){
      while(i < clue.length()){
        piece = clue.substr(i, MENU_WIDTH-2);
        mvprintw(++this->line, TEXT_X,piece.c_str());
        i += MENU_WIDTH-2;
      }
    }
  }
}

void Menu::displayTool(vector<Tool *> tool) {
  mvprintw(++this->line, TEXT_X, "Tool: ");

  for(unsigned int i = 0;i < tool.size(); i++) {
	  mvprintw(++this->line, TEXT_X,"%d. %s",i+1, tool[i]->getName().c_str());
  }
}


void Menu::displayInventory(){
	this->line +=2;
	mvprintw(++this->line, TEXT_X, "Inventory: [Strength] ");
	if(player->hasBinoculars())
	  mvprintw(++this->line, TEXT_X, "[] Binoculars");
	if(player->hasShip())
	  mvprintw(++this->line, TEXT_X, "[] Ship");
	++this->line;
	Tool** tools = player->getTools();
	int toolCount = player->getNumberOfTool();
	if((tools) == NULL)	return;
	for(int k =0; k< toolCount; ++k){
	  if(tools[k]!= NULL)
	    mvprintw(this->line++, TEXT_X, "[%d] %s", tools[k]->getStrength(), tools[k] ->getName().c_str());
	}

	return;
}

void Menu::displayInventory(int keyInput){
	if(keyInput == 'i' ){
	  if(!showInventory)
	    this->showInventory = true;
	  else
		  this->showInventory = false;
	}
}
