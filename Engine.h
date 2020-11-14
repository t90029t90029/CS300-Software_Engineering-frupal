#include "Map.h"

class Engine {
  public:
    Engine();
    bool isGameOver();
  
  private:
    Map map;
    Player player;
};
