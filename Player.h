#pragma once
#include "Map.h"
#include "Item.h"

#define MAX_INVENTORY 10

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
    void setBinoculars(bool value);

    // If player has ship, true
    bool hasShip(void);
    void setShip(bool value);

    // If player has a tool for this obstacle type,
    // the strength of the tool is returned
    // Otherwise, -1
    int hasTool(ObstacleType type);

    // Returns false if inventory is full
    bool addTool(Item * tool);

    // Get array of tools in inventory
    Tool ** getTools(void);
  private:
    // Inventory is array of tool pointers
    Tool * tools[MAX_INVENTORY];
    int toolCount;

    bool binoculars;
    bool ship;

    int energy;
    int money;

    int y;
    int x;
};
