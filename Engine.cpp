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

  map.load();
  menu.init(&map, &player);

  map.display(0, 0);
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
  int x = 0, y = 0;
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

  player.move(y, x);
  foundItem(y,x);
  map.display(y, x);
  menu.display();
}

bool Engine::isGameOver() {
  return !player.isAlive();
}

int Engine::northSwamp(){
  int y,x;
  int count = 0;
  player.locate(y,x);
  Tile * tile = map.getTile(y,x);
  while(tile->type != SWAMP && y > 0){
    --y;
    ++count;
    tile = map.getTile(y,x);
  }
  if(tile->type != SWAMP && y == 0)
    return -1;
  return count;
}

void Engine::foundItem(int y,int x){
  Tile * tile = map.getTile(y,x);
  char item = tile->item;
  int money = player.getMoney();
  int energy = player.getEnergy();
  int random;	//random number
  int coin;	//0 or 1
  int swamp;
  std::string clue;

  switch(item){
    case '$':
	    tile->item = ' ';
	    money += rand() % 901 + 100;
	    player.setMoney(money);
	    break;

    case 'F':
	    if(tile->food == CRACKER){
	      money -= 50;
	      if(money < 0){
	        //a menu function :inform the player the item is too expensive
		break;
	      }
	      player.setMoney(money);
	      energy += 20;
	      if(energy > 100)
	        energy = 100;
	      player.setEnergy(energy);
	    }
	    else if(tile->food == STEAK){
	      money -= 200;
	      if(money < 0){
	        //a menu function :inform the player the item is too expensive
		break;
	      }
	      player.setMoney(money);
	      energy = 100;
	      player.setEnergy(energy);
	    }
	    else if(tile->food == SPRITE){
	      money -= 80;
	      if(money < 0){
	        //a menu function :inform the player the item is too expensive
		break;
	      }
	      player.setMoney(money);
	      energy += 30;
	      if(energy > 100)
	        energy = 100;
	      player.setEnergy(energy);
	    }
	    tile->food = NON;
	    tile->item = ' ';
	    break;

    case '?':
	    coin = rand() % 2;
	    random = rand() % 128 + 1;
	    swamp = northSwamp();

	    //tell the truth
	    if(coin){
	      if(swamp != -1){
	        clue = "You are "+ std::to_string(x) +" grovnicks from the western border, there is a swamp "+ std::to_string(swamp) +" grovniks to the north, ";
	      }
	      else{
	        clue = "You are"+ std::to_string(x) +" grovnicks from the western border, there is no swamp to the north, ";
	      }

	      //TODO call the function to get the position of the diamond;
	      clue += "and the royal diamonds are located y grovnicks to the East and z grovnicks to the South.";
	    }
	   
	    //tell the lie
	    else{
	      clue = "You are"+ std::to_string(y) +" grovnicks from the western border, there is no swamp to the north, and the royal diamonds are located "+ std::to_string(random) +" grovnicks to the East ";
	      random = rand() % 128 + 1;
	      clue += "and "+ std::to_string(random) +" grovnicks to the South.";
	    }
	    // TODO make the clue be stored in the menu class
	    tile->item = ' ';
	    break;

    default: 
	    break;
  }
  return;
}
