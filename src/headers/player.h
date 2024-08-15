#pragma once
#include "map.h"
#include <SFML/System/Vector2.hpp>

class Player {
  sf::Vector2<float> position;  // The player's position vector
  sf::Vector2<float> direction; // The player's direction vector
  sf::Vector2<float> plane;     // The player's velocity vector

  float size;

  sf::Texture texture;

public:
  sf::Sprite sprite;

  Player(float x, float y);

  void draw(sf::RenderWindow *window);
  void update(sf::RenderWindow *window, Map *map, float *dt);
  void setPosition(float x, float y);
};
