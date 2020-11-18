#include "Menu.h"

void Menu::display(Player *player, Map *map) {
  int x, y;
  player->locate(y, x);

  int energy = player->getEnergy();
  int money = player->getMoney();

  int menuX = COLS - MENU_WIDTH;
  int textX = menuX + 2;

  mvvline(0, menuX, MENU_BORDER, LINES);


  mvprintw(2, textX, "> Item: Description");
  mvprintw(3, textX, "> Cost: #");
  mvprintw(4, textX, "> Energy: #");

  mvprintw(5, textX, "Options:");
  mvprintw(6, textX, "Up)    North");
  mvprintw(7, textX, "Left)  East");
  mvprintw(8, textX, "Right) West");
  mvprintw(9, textX, "Down)  South");

  mvprintw(LINES - 3, textX, "Whiffles: %d", money);
  mvprintw(LINES - 2, textX, "Energy: %d", energy);
}
