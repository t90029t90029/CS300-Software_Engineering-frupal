#pragma once
#include "Map.h"
#include "Item.h"

#define INVENTORY_MAX 10

class Player {
  public:
    Player();
    void locate(int &y, int &x);
    void move(int y, int x);
    bool isAlive(void);
    int getEnergy(void);
    int getMoney(void);
    void setEnergy(int value);
    void setMoney(int value);
    void setStartLocation(int playerStartY, int playerStartX);

    // If player has binoculars, true
    bool hasBinoculars(void);

    // If player has ship, true
    bool hasShip(void);

    // If player has a tool for this obstacle type,
    // the strength of the tool is returned
    // Otherwise, -1
    int hasTool(ObstacleType type);

    // Get array of tools in inventory
    Tool * getTools(void);
  private:
    // An array of tools in the inventory
    Tool * tools;
    int energy;
    int money;
    int y;
    int x;
};
