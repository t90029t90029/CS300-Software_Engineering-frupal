#include "Engine.h"

Engine::Engine() {
  // Initiate ncurses
  initscr();
  keypad(stdscr, true); // Accept keypad input
  cbreak();             // Allow game to break upon Ctrl+C
  noecho();             // Don't let user type

  curs_set(0); // Hide cursor, otherwise, background color of Player is overriden
}

void Engine::init() {
  map.load();
  map.display(0, 0);
  menu.display(&player, &map);
}

void Engine::receiveInput(int input) {
  switch (tolower(input)) {
  // Arrow keys
  case KEY_UP:
  case KEY_DOWN:
  case KEY_RIGHT:
  case KEY_LEFT:
    movePlayer(input);
    break;
  default:
    break;
  }
}

void Engine::movePlayer(int direction) {
  int x = 0, y = 0;
  player.locate(y, x);

  switch (direction) {
  // Arrow keys
  case KEY_UP:
    --y;
    break;
  case KEY_DOWN:
    ++y;
    break;
  case KEY_RIGHT:
    ++x;
    break;
  case KEY_LEFT:
    --x;
    break;
  }

  // Check Y is in bounds
  if (y < 0) y = 0;
  if (y > HEIGHT - 1) y = HEIGHT - 1;

  // Check X is in bounds
  if (x < 0) x = 0;
  if (x > WIDTH - 1) x = WIDTH - 1;

  player.move(y, x);
  map.display(y, x);
  menu.display(&player, &map);
}

bool Engine::isGameOver() {
  return !player.isAlive();
}
