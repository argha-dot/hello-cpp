#pragma once
#include "map.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Player {
  sf::Vector2<float> position;  // The player's position vector
  sf::Vector2<float> direction; // The player's direction vector
  sf::Vector2<float> plane;     // The player's velocity vector

  float size;

  sf::Texture texture;

  void rotatePlayer(float rotationSpeed);
  void handleMouse(sf::Window *window, float *dt);

public:
  sf::Sprite sprite;

  Player(float x, float y);
  Player(sf::Vector2<float> initPos);

  void draw(sf::RenderWindow *window);
  void update(sf::RenderWindow *window, Map *map, float *dt);
  void setPosition(float x, float y);

  void rayCast(Map *map, sf::RenderWindow *window);
};
