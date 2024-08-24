#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "map.h"
#include "player.h"

class Game {
  sf::ContextSettings settings;
  sf::RenderWindow window;

  sf::Texture textureMap;

  float dt;
  sf::Clock clock;
  Map map;
  Player player;

public:
  sf::VertexArray lines;
  sf::RenderStates state;

  // This is where the game puts everything
  sf::Image windowImage;
  // This gets rendered
  sf::Texture windowTexture;
  sf::Sprite windowSprite;

  Game();
  void updateDelta();
  void draw();
  void update();
  void handleEvents();
  void run();
  ~Game();
};
