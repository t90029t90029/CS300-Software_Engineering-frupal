#pragma once

#include <ncurses.h>
#include "Map.h"
#include "Player.h"

#define MENU_WIDTH 25
#define MENU_BORDER '#'

class Menu {
  public:
    void init(Map *m, Player *p);
    void display(void);

    void displayTool(vector<Tool*> tool);

  private:
    int MENU_X;
    int TEXT_X;

    Map *map;
    Player *player;
    int line;

    void displayOptions(int y, int x);
    void displayTile(int y, int x);
    void displayClue(void);
    void clear(void);
};
