#include "Engine.h"
#include <sstream>

Engine::Engine() {
  // Initiate ncurses
  initscr();
  keypad(stdscr, true); // Accept keypad input
  cbreak();             // Allow game to break upon Ctrl+C
  noecho();             // Don't let user type

  curs_set(0); // Hide cursor, otherwise, background color of Player is overriden
}

void Engine::init() {
  // Seed random events
  srand(time(NULL));

  // Load the map and menu
  int x = 0, y = 0;
  map.load(y, x);
  player.move(y, x);
  menu.init(&map, &player);

  // Display the map and menu
  map.display(y, x, player.hasBinoculars());
  menu.display();
}

void Engine::receiveInput(int input) {
  int y = 0, x = 0;

  switch (tolower(input)) {
  // Arrow keys
  case KEY_UP:
  case KEY_DOWN:
  case KEY_RIGHT:
  case KEY_LEFT:
    movePlayer(input);
    break;
  // Enter key
  case 10:
    // Purchase item
    player.locate(y, x);
    foundItem(y, x);

    // Refresh the map
    map.display(y, x, player.hasBinoculars());
    menu.display();
    break;
  default:
    break;
  }
}

void Engine::movePlayer(int direction) {
  // energy cost, 1 for normal, 2 for swamp, 0 when boat
  int enCost = 1;

  // Locate the player
  int x = 0, y = 0;
  player.locate(y, x);

  // For item purchase, we want to move the player
  // but keep the symbol where it is visually
  int symbolY = y, symbolX = x;

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

  // Move player while adding limits of walls and energy consumption
  // Place-holder for checking different types
  TileType type;
  type = (*map.getTile(y, x)).type;

#ifdef NOCLIP
  if (false)
#else
  if(type == WALL || type == WATER)
#endif // NOCLIP
  {
	  //include a check for if player has boat
	  //waiting items inventory
     player.locate(y, x);
  }
  else if (type == SWAMP) {
	  ++enCost;
  }

  // Move and expend energy
  player.move(y, x);
  player.setEnergy(player.getEnergy()-enCost);

  // If item is purchasable, highlight it
  if (map.isPurchasable(y, x)) {
    map.display(symbolY, symbolX, player.hasBinoculars());
    map.highlightItem(y, x);
  }
  // Otherwise, interact with item
  else {
    foundItem(y,x);
    map.display(y, x, player.hasBinoculars());
  }
  menu.display();
}

bool Engine::isGameOver() {
  return !player.isAlive();
}

void Engine::foundItem(int y,int x) {
  // Grab tile
  Tile * tile = map.getTile(y,x);
  char item = tile->item;

  // No item on this tile
  if (item == ' ') return;

  // Stats that the tiles may need to reference
  Item * itemType = tile->itemType;
  int money = player.getMoney();
  int energy = player.getEnergy();
  TileType type = tile->type;

  // Clue variables
  std::ostringstream output;
  std::string clue;
  int randomY = rand() % HEIGHT;	// random number
  int randomX = rand() % WIDTH;	  // random number
  Tile * temp = map.getTile(randomY,randomX);	//random tile

  switch(item){
    // Treasure chest
    case '$':
      // Royal Diamond -- Player wins!
	    if(type == DIAMOND){
        player.setEnergy(0);
      }
      // Normal treasure
      else {
        // Pick up treasure
        money += itemType->getMoney();
        player.setMoney(money);

        // Remove from map
        tile->item = ' ';
      }
      break;
    // Food
    case 'F':
      // Buy item
	    player.setMoney(money - itemType->getCost());

      // Restore energy
	    energy += itemType->getStrength();
	    if(energy > 100)
	      energy = 100;
	    player.setEnergy(energy);

      // Remove from map
	    tile->item = ' ';
	    break;
    // Clue
    case '?':
	    //tell the truth
	    if (itemType->getTruth()) {
	      clue = "You are "+ std::to_string(x) +" grovnicks from the western border";

	      output << randomX << "," << randomY;

	      clue += "There is a "+ temp->enumToString(temp->type) +" at ("+ output.str() +").";
	    }

	    //tell the lie
	    else {
	      clue = "You are "+ std::to_string(y) +" grovnicks from the western border";

	      output << randomY << "," << randomX;	//in reverse order

	      clue += "There is a "+ temp->enumToString(temp->type) +" at ("+ output.str() +").";
	    }

	    itemType->setClue(clue);
	    tile->item = ' ';
	    break;
    default:
	    break;
  }
  return;
}
