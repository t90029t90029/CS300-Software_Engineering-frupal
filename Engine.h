#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include <ctype.h>

class Engine {
  public:
    Engine();
    void init();
    void receiveInput(int input);
    void movePlayer(int direction);
    bool isGameOver();

  private:
    Map map;
    Menu menu;
    Player player;
};
