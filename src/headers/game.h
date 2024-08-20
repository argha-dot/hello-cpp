#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "map.h"
#include "player.h"

class Game {
  sf::ContextSettings settings;
  sf::RenderWindow window;

  sf::Texture textureMap;

  sf::RectangleShape floor;
  float dt;
  sf::Clock clock;
  Map map;
  Player player;

public:
  sf::VertexArray lines;

  Game();
  void updateDelta();
  void draw();
  void update();
  void handleEvents();
  void run();
  ~Game();
};
