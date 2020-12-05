#include "Menu.h"
#include <string>
#include <cstring>
using namespace std;

void Menu::init(Map * m, Player * p) {
  this->line = 0; // This determines which line to print on
  this->showInventory = false;
  this->map = m;
  this->player = p;

  int y = 0, x = 0;
  player->locate(y, x);
  this->cursor_y = y;
  this->cursor_x = x;
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
  displayTile(cursor_y, cursor_x);

  // Display player inventory, opens with key: I
  if(showInventory ){
	if(LINES < 38){
	  --this->line;
	  displayInventory();
	}else{//if terminal space allows, show all menu
	  displayOptions(y, x);
	  displayClue();
	  displayInventory();
	}
  }else{
  // Display options for current tile
	  displayOptions(y, x);

  // Display the clue if there is a clue
	  displayClue();
  }
  displayStats();
}

void Menu::displayStats() {
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
	case MEADOW:
	   floor= "Meadow";
	   break;
	case WATER:
	   floor = "Water";
	   break;
	case WALL:
	   floor = "Wall";
	   break;
	case SWAMP:
	   floor = "Swamp";
	   break;
	case DIAMOND:
	   floor = "*+*+Diamond+*+*";
	   break;
	default:
	   break;
  }

  if (tile->isVisible) {
    mvprintw(++this->line, TEXT_X, "> Grovnik: %s", floor.c_str());

    // Tile may not have an item, or it may be removed from the map
    if (item != NULL && itemChar != ' ') {
      mvprintw(++this->line, TEXT_X, "> Item:" );
      mvprintw(++this->line, TEXT_X, "  %s ", item->getName().c_str() );

      //treasure does not work as expected, substitute detectoin method used
      if(0 < item->getMoney())
          mvprintw(++this->line, TEXT_X, "> Fortune: %d", item->getMoney());
      else if (itemChar != '!' && itemChar != '?')
        mvprintw(++this->line, TEXT_X, "> Cost: %d", item->getCost());

      if(itemChar == 'T' || itemChar == '!')//Tool or Obstacle
        mvprintw(++this->line, TEXT_X, "> Strength: %d", item->getStrength());
      else if(itemChar == 'B' || itemChar == 'S' || itemChar == '$' || itemChar == '?')
        ++this->line;
      else
        mvprintw(++this->line, TEXT_X, "> Energy: %d", item->getStrength());
    }
    else {
      this->line += 4;//keeping menu spacing consistent
    }

    int enCost = -1;
    if(tile->type == SWAMP) {
      --enCost;
    }
    else if(tile->type == WATER) {
      ++enCost;
    }
  }
  else {
    mvprintw(++this->line, TEXT_X, "> Grovnik: ?");
  }

  ++this->line; // Add separation line
}

void Menu::displayOptions(int y, int x) {
  string direction;  // Direction text

  mvprintw(++this->line, TEXT_X, "Options:"); // Option heading

  // If item is purchasable, display option to buy
  if (map->isPurchasable(y, x)) {
    Tile * tile = map->getTile(y, x);
    // First show error messages if player can't buy the item
    if (tile->item == 'B' && player->hasBinoculars()) {
      attron(COLOR_PAIR('E'));
      mvprintw(++this->line, TEXT_X, " You already have ");
      mvprintw(++this->line, TEXT_X, " binoculars. ");
      attroff(COLOR_PAIR('E'));
    }
    else if (tile->item == 'S' && player->hasShip()) {
      attron(COLOR_PAIR('E'));
      mvprintw(++this->line, TEXT_X, " You already have ");
      mvprintw(++this->line, TEXT_X, " a ship. ");
      attroff(COLOR_PAIR('E'));
    }
    else if (player->getMoney() <= tile->itemType->getCost()) {

      attron(COLOR_PAIR('E'));
      mvprintw(++this->line, TEXT_X, " Not enough whiffles ");
      mvprintw(++this->line, TEXT_X, " to buy this item! ");
      attroff(COLOR_PAIR('E'));
    }
    // If they can buy it, show the option
    else {
      attron(COLOR_PAIR('H'));
      mvprintw(++this->line, TEXT_X, "Enter) Buy Item ");
      attroff(COLOR_PAIR('H'));
    }
    ++this->line;
  }

  // Check tiles neighboring player's position
  for (int i = 0; i < 4; ++i) {
    int _y = y, _x = x;

    switch (i) {
    case 0:
      direction = "W)     North";
      --_y;
      break;
    case 1:
      direction = "A)     West";
      --_x;
      break;
    case 2:
      direction = "S)     South";
      ++_y;
      break;
    case 3:
      direction = "D)     East";
      ++_x;
      break;
    }

    // If the neigboring tile is passable, display the option to move
    Tile * tile = map->getTile(_y, _x);
    if (tile != NULL) {
      if (tile->type == MEADOW || tile->type == SWAMP || (tile->type == WATER && player->hasShip())) {
        mvprintw(++this->line, TEXT_X, direction.c_str());
      }
    }
  }

  ++this->line;
  mvprintw(++this->line, TEXT_X,"Up)    Inspect North");
  mvprintw(++this->line, TEXT_X,"Left)  Inspect West");
  mvprintw(++this->line, TEXT_X,"Down)  Inspect South");
  mvprintw(++this->line, TEXT_X,"Right) Inspect East");

  ++this->line;
  mvprintw(++this->line, TEXT_X,"I)     Inventory");

  if (player->hasClue(y, x)) {
    if (player->wantSeeClue()) {
      mvprintw(++this->line, TEXT_X,"C)     Hide Clue");
    }
    else {
      mvprintw(++this->line, TEXT_X,"C)     Show Clue");
    }
  }
}

void Menu::displayClue(void){
  //the position of the clue
  int y;
  int x;
  //the position of the target
  int targetY;
  int targetX;

  string clue;
  string piece;
  Tile * tile;
  long unsigned int i = 0;
  unsigned int marker = 0;

  if(player->wantSeeClue()){
    //if the player holds a clue, copy the coordinate into y,x
    if(player->hasClue(y,x)){
      tile = map->getTile(y, x);
      this->line += 2;
      mvprintw(this->line, TEXT_X,"Clue:");
      //if there is a clue, copy the content into the string and print it out
      if(tile->itemType->getDetails(clue,targetY,targetX)){
	      clue += ' ';//append space for lastof to grab at end of line
        while(i < clue.length()-1){
	  marker = clue.find_last_of(' ', i+MENU_WIDTH - 2);

          piece = clue.substr(i, marker-i);

          mvprintw(++this->line, TEXT_X, "%s", piece.c_str());
          i = marker+1;
	}
      }
    }
  }
}

void Menu::displayTool(vector<Tool *> tool) {

  attron(COLOR_PAIR('H'));
  mvprintw(++this->line, TEXT_X, " Choose a Tool: ");
  attroff(COLOR_PAIR('H'));

  if (tool.size() == 0) {
    mvprintw(++this->line, TEXT_X, " No tools available " );
    mvprintw(++this->line, TEXT_X, " for this obstacle. " );

    ++this->line;
    mvprintw(++this->line, TEXT_X, " Press any key ");
    mvprintw(++this->line, TEXT_X, " to engage barehanded ");
  }
  else {
    for(unsigned int i = 0;i < tool.size(); i++) {
      mvprintw(++this->line, TEXT_X,"%d. %s",i+1, tool[i]->getName().c_str());
    }

    ++this->line;
    mvprintw(++this->line, TEXT_X, " Press any other key ");
    mvprintw(++this->line, TEXT_X, " to engage barehanded ");
  }

}


void Menu::displayInventory(){
	++this->line;
	mvprintw(++this->line, TEXT_X, "Inventory: [Strength] ");
	if(player->hasBinoculars())
	  mvprintw(++this->line, TEXT_X, "[-] Binoculars");
	if(player->hasShip())
	  mvprintw(++this->line, TEXT_X, "[-] Ship");
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

void Menu::displayInventoryToggle(){

	  if(!showInventory)
	    this->showInventory = true;
	  else
		  this->showInventory = false;

}
