#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include <ctype.h>
#include <time.h>
#include <string>

class Engine {
  public:
    Engine();
    void init();
    void receiveInput(int input);
    void movePlayer(int direction);
    bool isGameOver();
    void foundItem(int,int);
    void updatePosition();
    bool isGameWon();
    void displayWin();
    void displayLose();
  private:
    Map map;
    Menu menu;
    Player player;
    bool gameWon;
};
