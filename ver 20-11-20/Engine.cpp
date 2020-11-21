#include "Engine.h"

Engine::Engine() {
  // Initiate ncurses
  initscr();
  keypad(stdscr, true); // Accept keypad input
  cbreak();             // Allow game to break upon Ctrl+C
  noecho();             // Don't let user type

  curs_set(0); // Hide cursor, otherwise, background color of Player is overriden
}

void Engine::init() {
  srand(time(NULL));
  int playerX;
  int playerY;

  map.load(playerY, playerX);
  map.viewportSize(LINES, COLS);
  player.setStartLocation(playerY, playerX);
  
  menu.init(&map, &player);
  player.locate(playerY, playerX);
  map.display(playerY, playerX);
  menu.display();
}

void Engine::receiveInput(int input) {
  switch (tolower(input)) {
  // Arrow keys
  case KEY_UP:
  case KEY_DOWN:
  case KEY_RIGHT:
  case KEY_LEFT:
    movePlayer(input);
    break;
  default:
    break;
  }
}

void Engine::movePlayer(int direction) {
  //energy cost, 1 for normal, 2 for swamp, 0 when boat
  int x = 0, y = 0, enCost = 1;
  player.locate(y, x);

  switch (direction) {
  // Arrow keys
  case KEY_UP:
    --y;
    break;
  case KEY_DOWN:
    ++y;
    break;
  case KEY_RIGHT:
    ++x;
    break;
  case KEY_LEFT:
    --x;
    break;
  }

  // Check Y is in bounds
  if (y < 0) y = 0;
  if (y > HEIGHT - 1) y = HEIGHT - 1;

  // Check X is in bounds
  if (x < 0) x = 0;
  if (x > WIDTH - 1) x = WIDTH - 1;
  //move player while adding limits of walls and energy consumption
  //holder for checking different types
  TileType type;
  type = (*map.getTile(y, x)).type;
  if(type == WALL || type == WATER){
	  //include a check for if player has boat
	  //waiting items inventory
     player.locate(y, x);
  }else if(type == SWAMP)
	  ++enCost;
  player.setEnergy(player.getEnergy()-enCost);
	  
  player.move(y, x);
  foundItem(y,x);
  map.display(y, x);
  menu.display();
}

bool Engine::isGameOver() {
  return !player.isAlive();
}

void Engine::foundItem(int y,int x){
  Tile * tile = map.getTile(y,x);
  char item = tile->item;
  int money = player.getMoney();
  int energy = player.getEnergy();
  int cost;
  int randomY;	//random number
  int randomX;	//random number
  int coin;	//0 or 1
  std::string clue;

  switch(item){
    case '$':
	    tile->item = ' ';
	    money += rand() % 901 + 100;
	    player.setMoney(money);
	    break;

    case 'F':
    	    cost = tile->getCost(tile->itemtype);
	    if(cost > money){
	      //a menu function :inform the player the item is too expensive
	      break;
	    }
	    player.setMoney(money-cost);

	    energy += tile->getEnergy(tile->itemtype);
	    if(energy > 100)
	      energy = 100;
	    player.setEnergy(energy);

	    tile->itemtype = NON;
	    tile->item = ' ';
	    break;

    case '?':
	    coin = rand() % 2;
	    randomY = rand() % 128 + 1;
	    randomX = rand() % 128 + 1;

	    //tell the truth
	    if(coin){
	        clue = "You are"+ std::to_string(x) +" grovnicks from the western border, there is no swamp to the north, ";

	      //TODO call the function to get the position of the diamond;
	      clue += "and the royal diamonds are located y grovnicks to the East and z grovnicks to the South.";
	    }
	   
	    //tell the lie
	    else{
	      clue = "You are"+ std::to_string(y) +" grovnicks from the western border, there is no swamp to the north, and the royal diamonds are located "+ std::to_string(randomX) +" grovnicks to the East ";
	      clue += "and "+ std::to_string(randomY) +" grovnicks to the South.";
	    }

	    // TODO make the clue be stored in the menu class and clear the item
	    tile->item = ' ';
	    tile->itemtype = NON;
	    break;

    default: 
	    break;
  }
  return;
}
