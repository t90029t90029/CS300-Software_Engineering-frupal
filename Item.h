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

enum ObstacleType {
  BOULDER,
  TREE,
  MONSTER
};

enum FoodType {
  SNACK,
  MEAL,
  FEAST
};

class Item {
  public:
    Item(){};
    ~Item(){};
    virtual int getCost() = 0;
    virtual int getStrength() = 0;
    virtual ObstacleType getObstacle() = 0;
    virtual int getDetails(string&,int&,int&) = 0;
    virtual int getMoney() = 0;
    virtual int getTruth() = 0;
    virtual void setClue(string,int,int) = 0;
    virtual string getName(){ return "";};
    ItemType getType(void);
  private:
    ItemType type;
};

class Tool: public Item {
  public:
    Tool();
    ~Tool();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails(string&,int&,int&);
    int getMoney();
    int getTruth();
    void setClue(string,int,int);
    string getName();
  private:
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
    int getDetails(string&,int&,int&);
    int getMoney();
    int getTruth();
    void setClue(string,int,int);
    string getName();
  private:
    ObstacleType type;
    int energy;
    string name;
};

class Food: public Item {
  public:
    Food();
    ~Food();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails(string&,int&,int&);
    int getMoney();
    int getTruth();
    void setClue(string,int,int);
    string getName();
  private:
    FoodType type;
    string name;
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
    int getDetails(string&,int&,int&);
    int getMoney();
    int getTruth();
    void setClue(string,int,int);
    string getName();
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
    int getDetails(string&,int&,int&);
    int getMoney();
    int getTruth();
    void setClue(string,int,int);
    string getName(void);
  private:
    ClueType type;
    string isTrue;
    string content;
    int targetY;
    int targetX;
};

class Binoculars: public Item {
  public:
    Binoculars();
    ~Binoculars();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails(string&,int&,int&);
    int getMoney();
    int getTruth();
    void setClue(string,int,int);
    string getName();
  private:
    int value;
};

class Ship: public Item {
  public:
    Ship();
    ~Ship();
    int getCost();
    int getStrength();
    ObstacleType getObstacle();
    int getDetails(string&,int&,int&);
    int getMoney();
    int getTruth();
    void setClue(string,int,int);
    string getName();
  private:
    int value;
};
