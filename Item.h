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

enum ObstacleType{
  BOULDER,
  TREE,
  SOIL
}; 

enum ToolType{
  AXE,
  HOE,
  PICKAXE,
  SHOVEL
};

class Item {
  public:
    Item(){};
    ~Item(){};
    virtual int getCost() = 0;
    virtual int getStrength() = 0;
    virtual ObstacleType getObstacle() = 0;
    virtual int getDetails() = 0;
  private:
    ItemType type;
    string name;
};




class Obstacle: public Item {
  public:
    Obstacle();
    ~Obstacle();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails();
  private:
    ObstacleType type;
    int energy;
};


class Tool: public Item {
  public:
    Tool();
    ~Tool();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails();
  private:
    ToolType type;
    string name;
    int cost;
    int rating;
    ObstacleType obstacleType;
};

