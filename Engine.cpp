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
  map.display(y, x);
  menu.display();
}

bool Engine::isGameOver() {
  return !player.isAlive();
}
