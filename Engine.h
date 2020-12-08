#include "Map.h"
#include "Menu.h"
#include "Player.h"
#include <ctype.h>
#include <string>
#include <time.h>

class Engine {
public:
  Engine();
  void init();
  void receiveInput(int input);
  void movePlayer(int direction);
  bool isGameOver();
  void foundItem(int, int);
  void updatePosition();
  bool isGameWon();
  void displayWin();
  void displayLose();
  void moveCursor(int direction);

private:
  Map map;
  Menu menu;
  Player player;
  bool gameWon;
  int cursor_y;
  int cursor_x;
};
