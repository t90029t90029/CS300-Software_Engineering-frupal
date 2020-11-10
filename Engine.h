#include "Map.h"
#include "Player.h"

class Engine {
  public:
    Engine();
    bool isGameOver();
  
  private:
    Map map;
    Player player;
};