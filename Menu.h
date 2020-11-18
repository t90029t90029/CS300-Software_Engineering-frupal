#pragma once

#include <ncurses.h>
#include "Map.h"
#include "Player.h"

const int MENU_WIDTH = 25;

class Menu {
  public:
    void init(Map *m, Player *p);
    void display(void);

  private:
    const char MENU_BORDER = '#';
    int MENU_X;
    int TEXT_X;

    Map *map;
    Player *player;

    void displayOptions(int y, int x);
    void displayTile(int y, int x);
    void clear(void);
};
