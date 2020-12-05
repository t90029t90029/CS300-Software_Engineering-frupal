#include "Engine.h"
#include <sstream>
#include <math.h>

Engine::Engine() {
  // Initiate ncurses
  initscr();
  keypad(stdscr, true); // Accept keypad input
  cbreak();             // Allow game to break upon Ctrl+C
  noecho();             // Don't let user type
  start_color();

  curs_set(0);
  init_pair('E', COLOR_WHITE, COLOR_RED);     // Error
  init_pair('H', COLOR_BLACK, COLOR_YELLOW);  // Highlight

  // Set map colors
  map.init();
  gameWon = false;
}

void Engine::init() {
  // Seed random events
  srand(time(NULL));

  // Load the map and menu
  int x = 0, y = 0;
  map.load(y, x);
  player.move(y, x);
  menu.init(&map, &player);

  // Set cursor position
  cursor_x = x;
  cursor_y = y;

  // Display the map and menu
  map.display(y, x, player.hasBinoculars());
  menu.display();
}

void Engine::receiveInput(int input) {
  int y = 0, x = 0;

  //toggle inventory on/off
  switch (tolower(input)) {
  case 'i':
    menu.displayInventoryToggle();
    menu.display();
    break;
  // Arrow keys
  case KEY_UP:
  case KEY_DOWN:
  case KEY_RIGHT:
  case KEY_LEFT:
    moveCursor(input);
    break;
  // Moving keys
  case 'w':
  case 's':
  case 'd':
  case 'a':
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
  // Detect window resize and refresh
  case KEY_RESIZE:
    player.locate(y, x);
    map.display(y, x, player.hasBinoculars());
    menu.display();
    break;

  // Refresh the clue menu
  case 'c':
    if(player.wantSeeClue())
      player.setSeeClue(false);
    else
      player.setSeeClue(true);
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
  case 'w':
    --y;
    break;
  case 's':
    ++y;
    break;
  case 'd':
    ++x;
    break;
  case 'a':
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

  // Move player, reset cursor
  player.move(y, x);
  cursor_x = x;
  cursor_y = y;
  menu.cursor_y = y;
  menu.cursor_x = x;

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

    menu.display();
  }
  // Otherwise, interact with item
  else {
    menu.display();
    foundItem(y,x);
    map.display(y, x, player.hasBinoculars());
  }
  //update the clue for the menu
  updatePosition();
  menu.display();

  player.locate(cursor_y, cursor_x);

}

bool Engine::isGameOver() {
#ifdef GODMODE
  return false || gameWon;
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
  int randomY = rand() % 51;	// random number
  int randomX = rand() % 51;	// random number
  Tile * temp;
  int dice = rand() % 4;

  bool isValid;
  bool isObstacle;
  string article;
  string typeName;

  // Tool variables
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
	  displayWin();
	}
        // Normal treasure
        else {
          // Pick up treasure
          money += itemType->getMoney();
          player.setMoney(money);
          menu.displayStats();

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
        menu.display();
        break;
      // Clue
      case '?':
        // find a diamond to show the clue
        if(dice == 0){
          // go through the whole map to find the diamond
          for(int i=0;i<HEIGHT-1;++i){
            for(int j=0;j<WIDTH-1;++j){
                temp = map.getTile(i,j);
              if(temp->type == 5){
          //update
                randomY = i;
                randomX = j;
          //break for loop
                i = HEIGHT;
          j = WIDTH;
              }
            }
          }
        }
        // find one of the other 7 kinds of items
        else {
          temp = NULL;

          // Obstacle isn't a useful item, so don't include it
          while(!temp || !temp->itemType || !isValid){
              randomY = rand() % 51;
              randomX = rand() % 51;
              temp = map.getTile(y-25+randomY,x-25+randomX);

              if (temp) {
                if (temp->itemType != NULL) {
                  isObstacle = (temp->itemType->getType() == OBSTACLES);
                  isValid = (tile->itemType->getTruth() && !isObstacle) ||
                            (!tile->itemType->getTruth() && isObstacle);
                }

              else {
                isObstacle = false;
                isValid = false;
              }
             }

              else {
                isObstacle = false;
                isValid = false;
              }
          }
          //update
          randomY = y-25+randomY;
          randomX = x-25+randomX;
        }

        // The clue just needs to be non-blank to register with updatePosition();
        clue = "1";
        // store the content in the tile of Clue
        itemType->setClue(clue,randomY,randomX);

        // store the position of the clue in the player
        player.setClue(true,y,x);

        menu.display();
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
  string article;
  char fc;
  string plural;
  string typeName;

  //if the player has a clue, get the position of the clue
  if(player.hasClue(y,x)){
    //point to the clue
    tile = map.getTile(y,x);
    itemType = tile->itemType;

    //get the position of the target
    if(itemType->getDetails(clue,targetY,targetX)){
      // Reveal lie
      int dist = player.hasBinoculars() ? 2: 1;
      if (!itemType->getTruth() && (abs(py - targetY) <= dist && abs(px - targetX) <= dist)) {
        clue = "FOOL! There is no diamond here. You have fallen victim to one of the classic blunders!";
      }
      else {
        temp = map.getTile(targetY,targetX);

        if (!temp->itemType)
          typeName = temp->enumToString(temp->type);
        else
          typeName = temp->itemType->enumToString();

        // LIE
        if (!itemType->getTruth()) {
          typeName = "Royal Diamond";
        }

        // This section just does English grammar stuff
        fc = tolower(typeName[0]); //first char

        // Vowels
        article = "a";
        if (fc == 'a' || fc == 'e' || fc == 'i' || fc == 'o' || fc == 'u') {
          article = "an";
        }
        if (typeName == "food") {
          article = "some";
        }
        plural = "is";
        if (typeName == "binoculars") {
          article = "a pair of";
        }

        bool truth = itemType->getTruth();

        // If we reach it dismiss clue
        if (abs(targetY - py) == 0 && abs(targetX - px) == 0) {
          clue = "You have found it!";
        }
        else {

          clue = "You are "+ std::to_string(px) +" grovnicks from the western border.               ";

    if(!temp->itemType)
            clue += "There "+plural+" "+article+" "+ typeName +" that "+ plural + " " + player.itemDirect(truth,targetY,targetX);
    else
            clue += "There "+plural+" "+article+" "+ typeName +" that "+ plural + " " +  player.itemDirect(truth,targetY,targetX);
        }
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
        erase();
        initscr();                              //initializes screen
        start_color();

        int y = floor(LINES/2);                 //calculates floor of half of the screens lines
        int x = floor(COLS/2);                  //calculates floor of half of the screens columns
        char boarder = '#';                     //variable to store rectangle boarder symbol
        int counter = 10;                        //counter for loops, set for vertical lines of rectangle
        char ending_message[] = "YOU WON!!!";
        char ending_message2[] = "You found the Royal Diamond worth one zillion zillion whiffles!!!";
        char ending_message3[] = "press any key to exit";
        char blank = ' ';
        init_pair(2, COLOR_BLUE, COLOR_CYAN);
        init_pair(1, COLOR_WHITE, COLOR_CYAN);

        for(int i = LINES; i >= 0; --i){
          for(int j = COLS; j >= 0; --j){
            attron(COLOR_PAIR(1));
            mvprintw(i, j, "%c", blank);
            attroff(COLOR_PAIR(1));
          }
        }
        //loops printing vertical "#" symbol line for rectangle
        while(counter > -10)
        {
                attron(COLOR_PAIR(1));
                mvprintw(y - counter, x+35, "%c", boarder);
                mvprintw(y - counter, x-36, "%c", boarder);
                attroff(COLOR_PAIR(1));
                --counter;
        }

        counter = 35;                           //counter for loops, reset for horizontal lines of rectangle creation

        //loops printing horizontal "#" symbol line for rectangle
        while(counter > -35)
        {
                attron(COLOR_PAIR(1));
                mvprintw(y+9, x-counter, "%c", boarder);
                mvprintw(y-10, x-counter, "%c", boarder);
                --counter;
                attroff(COLOR_PAIR(1));
        }

        attron(COLOR_PAIR(2));
        mvprintw(y-1,x-6, "%s", ending_message);                   //prints hello world! message in center of rectangle
        mvprintw(y,x-32, "%s", ending_message2);                   //prints hello world! message in center of rectangle
        mvprintw(y+10,x+14, "%s", ending_message3);                   //prints hello world! message in center of rectangle
        attroff(COLOR_PAIR(2));
        refresh();                                              //refreshes window
        getchar();                                              //waits for user to input a character
        endwin();                                               //ends ncurses window

}
void Engine::displayLose(){
        erase();
        initscr();                              //initializes screen
        start_color();
        int y = floor(LINES/2);                 //calculates floor of half of the screens lines
        int x = floor(COLS/2);                  //calculates floor of half of the screens columns
        char boarder = '#';                     //variable to store rectangle boarder symbol
        int counter = 14;                        //counter for loops, set for vertical lines of rectangle
        char ending_message[] = "YOU LOSE!";
        char ending_message2[] = "You died from exhaustion! Game Over.";
        char ending_message3[] = "press any key to exit";

	char blank = ' ';
        init_pair(1, COLOR_WHITE, COLOR_RED);
        init_pair(2, COLOR_BLACK, COLOR_RED);

        for(int i = LINES; i >= 0; --i){
          for(int j = COLS; j >= 0; --j){
            attron(COLOR_PAIR(1));
            mvprintw(i, j, "%c", blank);
            attroff(COLOR_PAIR(1));
          }
        }


       //loops printing vertical "#" symbol line for rectangle
        while(counter > -counter)
        {
                attron(COLOR_PAIR(2));
                mvprintw(y - counter, x+counter, "%c", boarder);
                mvprintw(y - counter, x-counter, "%c", boarder);
                attroff(COLOR_PAIR(2));
                --counter;
        }

        counter = 14;                           //counter for loops, reset for horizontal lines of rectangle creation

        //loops printing horizontal "#" symbol line for rectangle
        while(counter > -counter)
        {
                attron(COLOR_PAIR(2));
                mvprintw(y+counter, x+counter, "%c", boarder);
                mvprintw(y+counter, x-counter, "%c", boarder);
                attroff(COLOR_PAIR(2));
                --counter;
        }

        attron(COLOR_PAIR(1));

        mvprintw(y,x-4, "%s", ending_message);                   //prints hello world! message in center of rectangle
        mvprintw(y+1,x-15, "%s", ending_message2);                   //prints hello world! message in center of rectangle
        mvprintw(y+10,x+14, "%s", ending_message3);                   //prints hello world! message in center of rectangle
        attroff(COLOR_PAIR(1));
        refresh();                                              //refreshes window
        getchar();                                              //waits for user to input a character
        endwin();                                               //ends ncurses window

}

void Engine::moveCursor(int direction) {
	menu.display();
	int playerX =0, playerY=0;
	player.locate(playerY, playerX);
	map.display(playerY, playerX, player.hasBinoculars());

	switch(direction) {
		case KEY_UP:
			cursor_y--;
			break;
		case KEY_DOWN:
			cursor_y++;
			break;
		case KEY_LEFT:
			 cursor_x--;
			 break;
		case KEY_RIGHT:
			 cursor_x++;
			 break;
	}

  int shiftY = 0, shiftX = 0;
  map.getShift(shiftY, shiftX);

	// Check Y is in bounds of map
  if (cursor_y - shiftY < 0)
    cursor_y = shiftY;
  if (cursor_y - shiftY > LINES - 1)
    cursor_y = LINES + shiftY - 1;

  // Check X is in bounds of map
  if (cursor_x - shiftX < 0)
    cursor_x = shiftX;
  if (cursor_x - shiftX > COLS - MENU_WIDTH - 1)
    cursor_x = COLS - MENU_WIDTH + shiftX - 1;

  menu.cursor_y = cursor_y;
  menu.cursor_x = cursor_x;

  menu.display();
	map.highlightItem(cursor_y, cursor_x);
}
