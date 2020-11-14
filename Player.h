class Player {
  public:
    Player();
    void locate(int &y, int &x);
    void move(int y, int x);
    bool isAlive(void);
  private:
    int energy;
    int y;
    int x;
};
