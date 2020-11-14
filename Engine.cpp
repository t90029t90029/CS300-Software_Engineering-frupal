#include "Engine.h"

Engine::Engine() {
  map.loader();
}

bool Engine::isGameOver() {
  return (player.energy <= 0);
}
