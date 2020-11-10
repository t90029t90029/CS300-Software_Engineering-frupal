#include "Engine.h"

Engine::Engine() {

}

bool Engine::isGameOver() {
  return (player.energy <= 0);
}