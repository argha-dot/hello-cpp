#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum Block { Empty, Wall, IPlayer };

class Map {
  std::vector<std::vector<Block>> map;

  sf::Sprite wall_sprite;
  sf::Texture wall_texture;

public:
  Map();

  /**
   * Check if the given position is inside a wall or not
   * THE POSITION IS IN PIXELS, NOT THE POSITION IN THE VECTOR
   * Hence, if you want to check if player is colliding with wall,
   * send the raw (x, y)
   */
  bool check_if_wall(float x, float y);

  void draw(sf::RenderWindow *window);
};
