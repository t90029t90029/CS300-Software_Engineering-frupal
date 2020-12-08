#include "Menu.h"
#include <cstring>
#include <string>
using namespace std;

void Menu::init(Map *m, Player *p) {
  this->line = 0; // This determines which line to print on
  this->showInventory = false;
  this->showOptions = true;
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
  // Determined terminal height for showing clue or inventory: 46,
  // can comfortably play at 38 expected, until max inv.
  // if show inv & clue triggered, clue takes priority.
  if (LINES < 46) {
    if (showInventory) {
      //--this->line;
      displayOptions(y, x, false);
      if (player->wantSeeClue()) {
        displayClue();
      } else
        displayInventory();
    } else if (player->wantSeeClue()) {

      displayOptions(y, x, false);
      if (showOptions) {
        //--this->line;
        displayClue();
      }
    } else {
      if (showOptions) { // goes off when encounter obstacle
        displayOptions(y, x);
      }
    }
  } else {
    if (showOptions) {
      displayOptions(y, x);
      displayClue();
    } else {
      displayOptions(y, x, false);
    }
    if (showInventory)
      displayInventory();
  }
  displayStats();
}

void Menu::displayStats() {
  // Display player stats at the bottom
  int energy = player->getEnergy();
  int money = player->getMoney();

  mvprintw(LINES - 3, TEXT_X, "Whiffles: %d", money);

  const int threshold = 15;

  // Show energy in read when it gets low
  if (energy <= threshold)
    attron(COLOR_PAIR('E'));

  mvprintw(LINES - 2, TEXT_X, "Energy: %d", energy);

  if (energy <= threshold)
    attroff(COLOR_PAIR('E'));
}

void Menu::clear() {
  for (int i = 0; i < LINES; ++i) {
    move(i, MENU_X);
    clrtoeol(); // Clear to end of line
  }
}

void Menu::displayTile(int y, int x) {
  // Examine tile at player's position
  Tile *tile = map->getTile(y, x);
  char itemChar = tile->item;

  Item *item = tile->itemType;
  string floor = " ";

  // Pretty'ing the names of the tiles
  switch (tile->type) {
  case MEADOW:
    floor = "Meadow";
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
    floor = "*+Diamond+*";
    break;
  default:
    break;
  }

  if (tile->isVisible) {
    mvprintw(++this->line, TEXT_X, "> Grovnick: %s", floor.c_str());

    // Tile may not have an item, or it may be removed from the map
    if (item != NULL && itemChar != ' ') {
      mvprintw(++this->line, TEXT_X, "> Item:");
      mvprintw(++this->line, TEXT_X, "  %s ", item->getName().c_str());

      // Display info about what the tool can be used for
      if (itemChar == 'T') {
        mvprintw(++this->line, TEXT_X, "> Use: ");
        switch (item->getObstacle() - 1) {
        case BOULDER:
          mvprintw(++this->line, TEXT_X, "  Rocks");
          break;
        case TREE:
          mvprintw(++this->line, TEXT_X, "  Plants");
          break;
        case MONSTER:
          mvprintw(++this->line, TEXT_X, "  Monsters");
          break;
        }
      }

      // treasure does not work as expected, substitute detectoin method used
      if (0 < item->getMoney()) {
        mvprintw(++this->line, TEXT_X, "> Fortune: %d", item->getMoney());
      } else if (itemChar != '!' && itemChar != '?') {
        mvprintw(++this->line, TEXT_X, "> Cost: %d", item->getCost());
      }

      if (itemChar == 'T' || itemChar == '!') {
        mvprintw(++this->line, TEXT_X, "> Strength: %d", item->getStrength());
      } else if (itemChar == 'B' || itemChar == 'S' || itemChar == '$' ||
                 itemChar == '?') {
        ++this->line;
      } else {
        mvprintw(++this->line, TEXT_X, "> Energy: %d", item->getStrength());
      }
    } else {
      int enCost = -1;
      if (tile->type == SWAMP) {
        --enCost;
      } else if (tile->type == WATER) {
        ++enCost;
      }
      mvprintw(++this->line, TEXT_X, ">");
      mvprintw(++this->line, TEXT_X, ">");
      mvprintw(++this->line, TEXT_X, ">");
      mvprintw(++this->line, TEXT_X, "> Energy: %d", enCost);
    }
  } else {
    mvprintw(++this->line, TEXT_X, "> Grovnick: ?");
    mvprintw(++this->line, TEXT_X, ">");
    mvprintw(++this->line, TEXT_X, ">");
    mvprintw(++this->line, TEXT_X, ">");
    mvprintw(++this->line, TEXT_X, ">");
  }

  ++this->line; // Add separation line
}

void Menu::displayOptions(int y, int x) { displayOptions(y, x, true); }

void Menu::displayOptions(int y, int x, bool full) {
  string direction; // Direction text

  mvprintw(++this->line, TEXT_X, "Options:"); // Option heading

  // If item is purchasable, display option to buy
  if (map->isPurchasable(y, x)) {
    Tile *tile = map->getTile(y, x);
    // First show error messages if player can't buy the item
    if (tile->item == 'B' && player->hasBinoculars()) {
      attron(COLOR_PAIR('E'));
      mvprintw(++this->line, TEXT_X, " You already have ");
      mvprintw(++this->line, TEXT_X, " binoculars. ");
      attroff(COLOR_PAIR('E'));
    } else if (tile->item == 'S' && player->hasShip()) {
      attron(COLOR_PAIR('E'));
      mvprintw(++this->line, TEXT_X, " You already have ");
      mvprintw(++this->line, TEXT_X, " a ship. ");
      attroff(COLOR_PAIR('E'));
    } else if (player->getMoney() <= tile->itemType->getCost()) {
      attron(COLOR_PAIR('E'));
      mvprintw(++this->line, TEXT_X, " Not enough whiffles ");
      mvprintw(++this->line, TEXT_X, " to buy this item! ");
      attroff(COLOR_PAIR('E'));
    } else if (tile->item == 'T' &&
               player->getNumberOfTool() >= MAX_INVENTORY) {
      attron(COLOR_PAIR('E'));
      mvprintw(++this->line, TEXT_X, " You can only hold ");
      mvprintw(++this->line, TEXT_X, " %d tools at once ", MAX_INVENTORY);
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

  // We may not want to show directions in some cases
  if (full) {
    // Check tiles neighboring player's position
    for (int i = 0; i < 4; ++i) {
      int _y = y, _x = x;

      switch (i) {
      case 0:
        direction = "W) North";
        --_y;
        break;
      case 1:
        direction = "W) West";
        --_x;
        break;
      case 2:
        direction = "S) South";
        ++_y;
        break;
      case 3:
        direction = "D) East";
        ++_x;
        break;
      }

      // If the neigboring tile is passable, display the option to move
      Tile *tile = map->getTile(_y, _x);
      if (tile != NULL) {
        if (tile->type == MEADOW || tile->type == SWAMP ||
            (tile->type == WATER && player->hasShip())) {
          mvprintw(++this->line, TEXT_X, direction.c_str());
        }
      }
    }

    mvprintw(++this->line, TEXT_X, ">) Inspect");
  }

  if (player->wantSeeClue()) {
    if (showInventory)
      displayInventoryToggle();
  }

  if (!showInventory) {
    mvprintw(++this->line, TEXT_X, "I) Inventory");
  } else {
    mvprintw(++this->line, TEXT_X, "I) Close Inventory");
  }

  if (player->hasClue(y, x)) {
    if (player->wantSeeClue()) {
      mvprintw(++this->line, TEXT_X, "C) Hide Clue");
    } else {
      mvprintw(++this->line, TEXT_X, "C) Show Clue");
    }
  }
}

void Menu::displayClue(void) {
  // the position of the clue
  int y;
  int x;
  // the position of the target
  int targetY;
  int targetX;

  string clue;
  string piece;
  Tile *tile;
  long unsigned int i = 0;
  unsigned int marker = 0;

  if (player->wantSeeClue()) {
    // if the player holds a clue, copy the coordinate into y,x
    if (player->hasClue(y, x)) {
      tile = map->getTile(y, x);
      ++this->line;
      mvprintw(++this->line, TEXT_X, "Clue:");
      int lastLine = LINES - 4;
      // if there is a clue, copy the content into the string and print it out
      if (tile->itemType->getDetails(clue, targetY, targetX)) {
        clue += ' '; // append space for lastof to grab at end of line
        while (i < clue.length() - 1) {
          marker = clue.find_last_of(' ', i + MENU_WIDTH - 2);

          piece = clue.substr(i, marker - i);

          mvprintw(++this->line, TEXT_X, "%s", piece.c_str());

          i = marker + 1;

          if (this->line >= lastLine) {
            move(lastLine, TEXT_X);
            clrtoeol();
            mvprintw(lastLine, TEXT_X, "...");
            break;
          }
        }
      }
    }
  }
}

void Menu::displayTool(vector<Tool *> tool) {
  ++this->line;
  attron(COLOR_PAIR('H'));
  mvprintw(++this->line, TEXT_X, " Choose a Tool: [Power]");
  attroff(COLOR_PAIR('H'));

  if (tool.size() == 0) {
    mvprintw(++this->line, TEXT_X, " No tools available ");
    mvprintw(++this->line, TEXT_X, " for this obstacle. ");

    ++this->line;
    mvprintw(++this->line, TEXT_X, " Press any key ");
    mvprintw(++this->line, TEXT_X, " to engage barehanded ");
  } else {
    for (unsigned int i = 0; i < tool.size(); i++) {
      mvprintw(++this->line, TEXT_X, "%d. [%d] %s", i + 1,
               tool[i]->getStrength(), tool[i]->getName().c_str());
    }

    ++this->line;
    mvprintw(++this->line, TEXT_X, " Press any other key ");
    mvprintw(++this->line, TEXT_X, " to engage barehanded ");
  }
}

void Menu::displayInventory() {
  ++this->line;
  mvprintw(++this->line, TEXT_X, "Inventory: [Strength] ");

  Tool **tools = player->getTools();
  int toolCount = player->getNumberOfTool();
  if ((tools) == NULL ||
      (toolCount == 0 && !player->hasBinoculars() && !player->hasShip())) {
    mvprintw(++this->line, TEXT_X, "No tools yet");
  }

  int lastLine = LINES - 4;

  for (int k = 0; k < toolCount; ++k) {
    if (++this->line >= lastLine) {
      mvprintw(lastLine, TEXT_X, "...");
      break;
    } else {
      if (tools[k] != NULL)
        mvprintw(this->line, TEXT_X, "[%d] %s", tools[k]->getStrength(),
                 tools[k]->getName().c_str());
    }
  }

  if (this->line < lastLine) {
    if (player->hasBinoculars())
      mvprintw(++this->line, TEXT_X, "[-] Binoculars");
    if (player->hasShip())
      mvprintw(++this->line, TEXT_X, "[-] Ship");
  }

  return;
}

void Menu::displayInventoryToggle() {

  if (!showInventory) {
    player->setSeeClue(false);
    this->showInventory = true;
  } else {
    this->showInventory = false;
  }
}

bool Menu::showingInventory() { return showInventory; }
void Menu::toggleOptions() {
  if (showOptions)
    showOptions = false;
  else
    showOptions = true;
}
