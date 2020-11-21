#pragma once

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
  private:
    int energy;
    int money;
    int y;
    int x;
};
