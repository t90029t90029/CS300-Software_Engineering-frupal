#pragma once

#include "Map.h"
#include "Player.h"
#include <ncurses.h>

#define MENU_WIDTH 25
#define MENU_BORDER '#'

class Menu {
public:
  void init(Map *m, Player *p);
  void display(void);
  void displayTool(vector<Tool *> tool);
  // determines if inventory shows
  void displayInventoryToggle(void);
  bool showingInventory(void);
  void displayStats(void);
  // make space for obstacle tool selection
  void toggleOptions(void);
  void displayTile(int y, int x);
  void clear(void);

  int cursor_y;
  int cursor_x;

private:
  int MENU_X;
  int TEXT_X;

  Map *map;
  Player *player;
  int line;
  bool showInventory, showOptions;

  void displayOptions(int y, int x);
  void displayOptions(int y, int x, bool full);
  void displayClue(void);
  void displayInventory(void);
};
