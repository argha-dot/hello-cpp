#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "globals.h"

enum Block { Empty, Wall, Column, IPlayer };

class Map {

  sf::Sprite wall_sprite;
  sf::Texture wall_texture;

  sf::Sprite column_sprite;
  sf::Texture column_texture;

public:
  Map();

  std::vector<std::vector<Block>> map;

  /**
   * Check if the given position is inside a wall or not
   * THE POSITION IS IN PIXELS, NOT THE POSITION IN THE VECTOR
   * Hence, if you want to check if player is colliding with wall,
   * send the raw (x, y)
   */
  bool check_if_wall(float x, float y, float block_size = MAP_BLOCK_SIZE);

  Block getWall(int x, int y);
  sf::Vector2<float> getPlayerPosition(float block_size = MAP_BLOCK_SIZE);

  void draw(sf::RenderWindow *window);
};
