#pragma once

#include <SFML/Graphics.hpp>

#include "map.h"
#include "player.h"

class Game {
  sf::ContextSettings settings;
  sf::RenderWindow window;

  sf::RectangleShape floor;
  float dt;
  sf::Clock clock;
  Map map;
  Player player;

public:
  Game();
  void updateDelta();
  void draw();
  void update();
  void handleEvents();
  void run();
  ~Game();
};
