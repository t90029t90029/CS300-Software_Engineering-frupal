#include <ncurses.h>
#include <ctype.h>

#include "Engine.h"

#define INPUT_QUIT 'q'

int main() {
  Engine engine;
  char input;

  // Initiate ncurses
  initscr();
  keypad(stdscr, true); // Accept keypad input
  noecho();             // Don't let user type

  // Input loop until quit
  while ((input = getch()) != INPUT_QUIT && !engine.isGameOver()) {
    switch (tolower(input)) {
    // Arrow keys
    case KEY_UP:
    case KEY_DOWN:
    case KEY_RIGHT:
    case KEY_LEFT:
      break;
    }
  }

  getch();
  endwin();

  return 0;
}
