#include <ncurses.h>
#include <ctype.h>

#include "Engine.h"

#define INPUT_QUIT 'q'

int main() {
  Engine engine;
  int input;

  // Load and display map
  engine.init();

  // Input loop until quit
  while ((input = getch()) != INPUT_QUIT && !engine.isGameOver())
    engine.receiveInput(input);

  endwin();

  if(engine.isGameWon() == true)
    engine.displayWin();
  else if (input != INPUT_QUIT)
    engine.displayLose();

  return 0;
}
