#include <ctype.h>
#include <ncurses.h>

#include "Engine.h"

#define INPUT_QUIT 'q'

int main() {
  Engine engine;
  int input;

  // Load and display map
  engine.init();

  // Input loop until quit
  while (!engine.isGameOver() && (input = getch()) != INPUT_QUIT)
    engine.receiveInput(input);

  if (engine.isGameWon() == false && input != INPUT_QUIT)
    engine.displayLose();
  endwin();

  return 0;
}
