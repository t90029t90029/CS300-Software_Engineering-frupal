#pragma once
#include "Map.h"
#include "Item.h"
#include <vector>
#define MAX_INVENTORY 8

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

    // If player has clue, true
    bool hasClue(int & clueY,int & clueX);
    void setClue(bool value,int clueY,int clueX);

    // If player would like to read the clue
    bool wantSeeClue();
    void setSeeClue(bool value);

    // return the relative direction the item is from the palyer
    string itemDirect(bool truth,int itemY,int itemX);

    // If player has a tool for this obstacle type,
    // the strength of the tool is returned
    // Otherwise, -1
    vector<Tool*> hasTool(Item *obstacle);

    // Returns false if inventory is full
    bool addTool(Item * tool);

    bool removeTool(Tool* tool);

    int getNumberOfTool();

    // Get array of tools in inventory
    Tool ** getTools(void);
  private:
    // Inventory is array of tool pointers
    Tool * tools[MAX_INVENTORY];
    int toolCount;

    bool binoculars;
    bool ship;

    // Get the position of the last clue in the map
    int clueY;
    int clueX;
    bool clue;
    // a toggle for dismissing the clue
    bool seeClue;

    int energy;
    int money;

    int y;
    int x;
};
