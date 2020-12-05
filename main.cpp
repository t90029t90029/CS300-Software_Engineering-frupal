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
  while (!engine.isGameOver() && (input = getch()) != INPUT_QUIT)
    engine.receiveInput(input);

  if(engine.isGameWon() == false)
    engine.displayLose();
  endwin();
  
  return 0;
}
