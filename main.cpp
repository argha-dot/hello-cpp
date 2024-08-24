#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window.hpp>

#include "src/headers/game.h"
#include "src/headers/printStandard.h"

int main() {
  getStandard();

  Game game{};

  game.run();

  return 0;
}
