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
    int northSwamp();
    void foundItem(int,int);

  private:
    Map map;
    Menu menu;
    Player player;
};
