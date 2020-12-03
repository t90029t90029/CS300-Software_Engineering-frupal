#include "Engine.h"
#include <sstream>
#include <math.h>

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
    menu.displayInventory(input);
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
  // Traverse Water
  if (type == WATER && player.hasShip())
  {
    enCost = 0;
  }
  // Hit Wall
  else if(type == WALL || type == WATER)
#endif // NOCLIP
  {
	  //include a check for if player has boat
	  //waiting items inventory

     player.locate(y, x);
  }
  // Stuck in swamp
  else if (type == SWAMP) {
	  ++enCost;
  }

  player.move(y, x);

  // Move and expend energy
  player.setEnergy(player.getEnergy()-enCost);

  // If item is purchasable, highlight it
  if (map.isPurchasable(y, x)) {
    map.display(symbolY, symbolX, player.hasBinoculars());

    // If player moved onto the item, let the player symbol cover the item
    // This would only happen if the tile beyond the item was impassable
    // The normal behavior is that the player hops over the item
    if (symbolY != y || symbolX != x)
      map.highlightItem(y, x);
  }
  // Otherwise, interact with item
  else {
    foundItem(y,x);
    map.display(y, x, player.hasBinoculars());
  }
  //update the clue for the menu
  updatePosition();

  menu.display();
}

bool Engine::isGameOver() {
#ifdef GODMODE
  return false;
#else
  return !player.isAlive();
#endif // GODMODE
}

void Engine::foundItem(int y,int x) {
  // Grab tile
  Tile * tile = map.getTile(y,x);
  char item = tile->item;

  // No item on this tile
  if (item == ' ') return;

  // Stats that the tiles may need to reference
  Item * itemType = tile->itemType;
  TileType type = tile->type;

  int money = player.getMoney();
  int energy = player.getEnergy();
  int cost = 0;
  if (itemType != NULL)
    cost = itemType->getCost();

  // Clue variables
  std::string clue;
  int randomY = rand() % HEIGHT;  // random number
  int randomX = rand() % WIDTH;	  // random number
  Tile * temp = map.getTile(randomY,randomX);	//random tile

  int destroyEnergy;
  vector<Tool *> tools;
  int toolChoice = 0;


  // Purchasable items
  if (map.isPurchasable(y, x)) {
    int netMoney = money - cost;

    // Don't purchase if not enough money
    if (netMoney > 0) {
      switch (item) {
        // Food
        case 'F':
          // Buy item
          player.setMoney(netMoney);

          // Restore energy
          energy += itemType->getStrength();
          if(energy > 100)
            energy = 100;
          player.setEnergy(energy);

          // Remove from map
          tile->item = ' ';
          break;
        // Binoculars
        case 'B':
          if (!player.hasBinoculars()) {
            // Buy item, put in inventory, remove from map
            player.setMoney(netMoney);
            player.setBinoculars(true);
            tile->item = ' ';
          }
          break;
        // Ship
        case 'S':
          if (!player.hasShip()) {
            // Buy item, put in inventory, remove from map
            player.setMoney(netMoney);
            player.setShip(true);
            tile->item = ' ';
          }
          break;
        // Tool
        case 'T':
          // Buy item, put in inventory, remove from map
          player.setMoney(netMoney);
          player.addTool(itemType);
          tile->item = ' ';
          break;
        default:
          break;
        }
     }
  }
  // Non-purchasable items
  else {
    switch(item) {
      // Treasure chest
      case '$':
        // Royal Diamond -- Player wins!
        if(type == DIAMOND){
          player.setEnergy(0);
          gameWon = true;
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
      // Obstacle
      case '!':
        destroyEnergy = tile->itemType->getStrength();
        tools = player.hasTool(tile->itemType);

        int symbolY, symbolX;
        player.locate(symbolY, symbolX);
        map.display(symbolY, symbolX, player.hasBinoculars());
        map.highlightItem(y, x);
        menu.display();
        menu.displayTool(tools);

        toolChoice = getch() - 1 - '0';
        if(tools.size() != 0) {
          if(toolChoice >=0 && unsigned(toolChoice) < tools.size()) {
            // Strength starts at one but we want to divide by at least 2
            destroyEnergy /= (tools[toolChoice]->getStrength() + 1);
            player.removeTool(tools[toolChoice]);
          }
        }

        player.setEnergy(energy - destroyEnergy);
        tile->item = ' ';
        break;
      // Clue
      case '?':
        //tell the truth
        if (itemType->getTruth()) {
          clue = "You are "+ std::to_string(x) +" grovnicks from the western border. ";

          clue += "There is a "+ temp->enumToString(temp->type) +" that "+ player.itemDirect(true,randomY,randomX);
        }

        //tell the lie
        else {
          clue = "You are "+ std::to_string(y) +" grovnicks from the western border. ";

          clue += "There is a "+ temp->enumToString(temp->type) +" that "+ player.itemDirect(false,randomY,randomX);
        }

	//store the content in the tile of Clue
        itemType->setClue(clue,randomY,randomX);

	//store the position of the clue
	player.setClue(true,y,x);
        tile->item = ' ';
        break;
      default:
        break;
    }
  }
}

//the relative position between the target of the clue and the player
void Engine::updatePosition(){
  string clue;
  Tile * tile;
  Item * itemType;
  //the position of the clue
  int y;
  int x;
  //the position of the player
  int py;
  int px;
  player.locate(py,px);
  //the position of the target tile of the clue
  int targetY;
  int targetX;
  Tile * temp;

  //if the player has a clue, get the position of the clue
  if(player.hasClue(y,x)){
    //point to the clue
    tile = map.getTile(y,x);
    itemType = tile->itemType;

    //get the position of the target
    if(itemType->getDetails(clue,targetY,targetX)){
      temp = map.getTile(targetY,targetX);

      //tell the truth
      if (itemType->getTruth()) {
        clue = "You are "+ std::to_string(px) +" grovnicks from the western border. ";

        clue += "There is a "+ temp->enumToString(temp->type) +" that "+ player.itemDirect(true,targetY,targetX);
      }

      //tell the lie
      else {
        clue = "You are "+ std::to_string(y+(px-x)) +" grovnicks from the western border. ";

        clue += "There is a "+ temp->enumToString(temp->type) +" that "+ player.itemDirect(false,targetY,targetX);
      }

      //update the content in the tile of Clue
      itemType->setClue(clue,targetY,targetX);
    }
  }
}

bool Engine::isGameWon(){
  return gameWon;
}


void Engine::displayWin() {
        initscr();                              //initializes screen
        int y = floor(LINES/2);                 //calculates floor of half of the screens lines
        int x = floor(COLS/2);                  //calculates floor of half of the screens columns
        x = x-12;
        char boarder = '#';                     //variable to store rectangle boarder symbol
        int counter = 6;                        //counter for loops, set for vertical lines of rectangle
        char ending_message[] = "YOU WON!!!";
        char ending_message2[] = "You found the Royal Diamond worth one zillion zillion whiffles!!!";

        //loops printing vertical "#" symbol line for rectangle
        while(counter > -6)
        {
                mvprintw(y - counter, x+35, "%c", boarder);
                mvprintw(y - counter, x-36, "%c", boarder);
                --counter;
        }

        counter = 35;                           //counter for loops, reset for horizontal lines of rectangle creation

        //loops printing horizontal "#" symbol line for rectangle
        while(counter > -35)
        {
                mvprintw(y+5, x-counter, "%c", boarder);
                mvprintw(y-6, x-counter, "%c", boarder);
                --counter;
        }

        mvprintw(y-1,x-6, "%s", ending_message);                   //prints hello world! message in center of rectangle
        mvprintw(y,x-33, "%s", ending_message2);                   //prints hello world! message in center of rectangle
        refresh();                                              //refreshes window
        move(LINES-1,COLS-1);                                   //moves cursor to lower right corner of screen
        refresh();                                              //refreshes window
        getchar();                                              //waits for user to input a character
        endwin();                                               //ends ncurses window

}

void Engine::displayLose(){
        initscr();                              //initializes screen
        int y = floor(LINES/2);                 //calculates floor of half of the screens lines
        int x = floor(COLS/2);                  //calculates floor of half of the screens columns
        x = x-12;
        char boarder = '#';                     //variable to store rectangle boarder symbol
        int counter = 6;                        //counter for loops, set for vertical lines of rectangle
        char ending_message[] = "YOU LOSE!";
        char ending_message2[] = "You died from exhaustion! Game Over.";

        //loops printing vertical "#" symbol line for rectangle
        while(counter > -6)
        {
                mvprintw(y - counter, x+35, "%c", boarder);
                mvprintw(y - counter, x-36, "%c", boarder);
                --counter;
        }

        counter = 35;                           //counter for loops, reset for horizontal lines of rectangle creation

        //loops printing horizontal "#" symbol line for rectangle
        while(counter > -35)
        {
                mvprintw(y+5, x-counter, "%c", boarder);
                mvprintw(y-6, x-counter, "%c", boarder);
                --counter;
        }

        mvprintw(y,x-6, "%s", ending_message);                   //prints hello world! message in center of rectangle
        mvprintw(y+1,x-18, "%s", ending_message2);                   //prints hello world! message in center of rectangle
        refresh();                                              //refreshes window
        move(LINES-1,COLS-1);                                   //moves cursor to lower right corner of screen
        refresh();                                              //refreshes window
        getchar();                                              //waits for user to input a character
        endwin();                                               //ends ncurses window

}
