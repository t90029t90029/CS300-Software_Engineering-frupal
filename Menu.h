#pragma once

#include <ncurses.h>
#include "Map.h"
#include "Player.h"

const int MENU_WIDTH = 20;
const char MENU_BORDER = '#';

class Menu {
  public:
    void display(Player *player, Map *map);
};
