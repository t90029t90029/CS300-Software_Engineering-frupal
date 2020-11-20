#include <iostream>
#include <string>
#include <ncurses.h>
using namespace std;

enum ItemType {
  SHIP,
  BINOCULARS, 
  TOOLS,
  FOOD,
  OBSTACLES,
  CLUE,
  TREASURE
};


class Item {
  public:
    Item(){};
    ~Item(){};
    int getCost();
    int getStrength();
    int getObstacle();
    int getDetails();
  private:
    ItemType type;
    string name;
};

enum ToolType{
  AXE,
  HOE,
  PICKAXE,
  SHOVEL
};

class Tool: public Item {
  public:
    Tool();
    ~Tool();
    int getCost();
    int getStrength();
    int getObstacle();
    int getDetails();
  private:
    ToolType type;
    string name;
    int cost;
    int rating;
};


enum ObstacleType{
  BOULDER,
  TREE
}; 
class Obstacle: public Item {
  public:
    Obstacle();
    ~Obstacle();
    int getCost();
    int getStrength();
    int getObstacle();
    int getDetails();
  private:
    ObstacleType type;
    int energy;
};
