#include "Menu.h"
#include <string>

using namespace std;

void Menu::init(Map * m, Player * p) {
  this->line = 0; // This determines which line to print on
  this->map = m;
  this->player = p;
}

void Menu::display() {
  // Reset line position
  this->line = 0;

  // Determine where we're printing
  MENU_X = COLS - MENU_WIDTH;
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

  mvprintw(++this->line, TEXT_X, "> Grovnik: %d", tile->type);

  if (tile->item != NULL) {
    mvprintw(++this->line, TEXT_X, "> Cost: ?");
    mvprintw(++this->line, TEXT_X, "> Energy: ?");
  }

  ++this->line; // Add separation line
}

void Menu::displayOptions(int y, int x) {
  string direction;  // Direction text


  mvprintw(++this->line, TEXT_X, "Options:"); // Option heading

  //Examine tile at player's position
  Tile * tile = map->getTile(y, x);

  // If it has an item, display info about it
  if (tile->item != NULL) {
    mvprintw(++this->line, TEXT_X, "Enter) Buy");
  }

  // Check tiles neighboring player's position
  for (int i = 0; i < 4; ++i) {
    int _y = y, _x = x;

    switch (i) {
    case 0:
      direction = "Up)    North";
      --_y;
      break;
    case 1:
      direction = "Left)  East";
      --_x;
      break;
    case 2:
      direction = "Right) West";
      ++_x;
      break;
    case 3:
      direction = "Down)  South";
      ++_y;
      break;
    }

    // If the neigboring tile is passable, display the option
    tile = map->getTile(_y, _x);
    if (tile != NULL) {
      if (tile->type == MEADOW || tile->type == SWAMP) {
        mvprintw(++this->line, TEXT_X, direction.c_str());
      }
    }
  }
}