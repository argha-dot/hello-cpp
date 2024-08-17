#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "src/headers/globals.h"
#include "src/headers/map.h"
#include "src/headers/player.h"
#include "src/headers/printStandard.h"

void updateDelta(float *dt, sf::Clock *clock) {
  *dt = clock->restart().asSeconds();
}

int main() {
  getStandard();

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Hello CPP", sf::Style::Default, settings);

  window.setVerticalSyncEnabled(true);
  window.setMouseCursorVisible(false);
  window.setMouseCursorGrabbed(true);
  window.setActive(true);

  float dt;
  sf::Clock clock;

  Map map{};
  Player player(map.getPlayerPosition(1));

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
      }
    }

    updateDelta(&dt, &clock);
    player.update(&window, &map, &dt);

    window.clear(sf::Color::Black);
    player.rayCast(&map, &window);
    map.draw(&window);
    player.draw(&window);

    window.display();
  }

  return 0;
}
