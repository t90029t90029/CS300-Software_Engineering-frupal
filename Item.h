#pragma once

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
    virtual int getDetails(string&) = 0;
    virtual int getMoney() = 0;
    virtual int getTruth() = 0;
    virtual void setClue(string) = 0;
    virtual int getToggle() = 0;
    ItemType getType(void);
  private:
    ItemType type;
    string name;
};

class Tool: public Item {
  public:
    Tool();
    ~Tool();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails(string&);
    int getMoney();
    int getTruth();
    void setClue(string);
    int getToggle();
  private:
    ToolType type;
    string name;
    int cost;
    int rating; ObstacleType obstacleType;
};

class Obstacle: public Item {
  public:
    Obstacle();
    ~Obstacle();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails(string&);
    int getMoney();
    int getTruth();
    void setClue(string);
    int getToggle();
  private:
    ObstacleType type;
    int energy;
};

enum FoodType {
  CRACKER,
  STEAK,
  SPRITE
};
class Food: public Item {
  public:
    Food();
    ~Food();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails(string&);
    int getMoney();
    int getTruth();
    void setClue(string);
    int getToggle();
  private:
    FoodType type;
    int energy;
    int cost;
};

class Treasure: public Item {
  public:
    Treasure();
    ~Treasure();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails(string&);
    int getMoney();
    int getTruth();
    void setClue(string);
    int getToggle();
  private:
    int value;
};

enum ClueType {
  TRUTH,
  LIE
};
class Clue: public Item {
  public:
    Clue();
    ~Clue();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails(string&);
    int getMoney();
    int getTruth();
    void setClue(string);
    int getToggle();
  private:
    ClueType type;
    string isTrue;
    string content;
    int toggle;
};
