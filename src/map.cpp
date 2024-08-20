#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "headers/globals.h"
#include "headers/map.h"

Map::Map()
    : wall_sprite(wall_texture), column_sprite(column_texture),
      door_sprite(door_texture) {

  if (!wall_texture.loadFromFile("src/assets/images/wall.png")) {
    std::cout << "Error Opening Texture" << std::endl;
  }

  if (!column_texture.loadFromFile("src/assets/images/column.png")) {
    std::cout << "Error Opening Texture" << std::endl;
  }

  if (!door_texture.loadFromFile("src/assets/images/door.png")) {
    std::cout << "Error Opening Texture" << std::endl;
  }

  std::ifstream levelFile("src/assets/levels/level1");

  if (!levelFile.is_open()) {
    std::cerr << "Error Opening File" << "\n";
  }

  std::string line;

  map = {};

  while (std::getline(levelFile, line)) {
    std::vector<Block> map_row;
    int row_len{
        static_cast<int>(line.size())}; // converting long unsigned int to int

    for (int row = 0; row < row_len; row++) {
      char ch = line[row];
      if (ch == '#') {
        map_row.push_back(Block::Wall);
      } else if (ch == 'P') {
        map_row.push_back(Block::IPlayer);
      } else if (ch == '@') {
        map_row.push_back(Block::Column);
      } else if (ch == 'D') {
        map_row.push_back(Block::Door);
      } else {
        map_row.push_back(Block::Empty);
      }
    }

    map.push_back(map_row);
  }
  levelFile.close();
}

sf::Vector2<float> Map::getPlayerPosition(float block_size) {

  int col_len{
      static_cast<int>(map.size())}; // converting long unsigned int to int

  for (int col = 0; col < col_len; col++) {
    int row_len{static_cast<int>(
        map[col].size())}; // converting long unsigned int to int

    for (int row = 0; row < row_len; row++) {
      if (map[col][row] == Block::IPlayer) {
        return sf::Vector2<float>(row * block_size, col * block_size);
      }
    }
  }

  return sf::Vector2<float>(15 * block_size, 10 * block_size);
}

void Map::draw(sf::RenderWindow *window) {
  int col_len{
      static_cast<int>(map.size())}; // converting long unsigned int to int

  for (int col = 0; col < col_len; col++) {
    int row_len{static_cast<int>(
        map[col].size())}; // converting long unsigned int to int

    for (int row = 0; row < row_len; row++) {
      if (map[col][row] == Block::Wall) {
        wall_sprite.setPosition(MAP_BLOCK_SIZE * row, MAP_BLOCK_SIZE * col);
        wall_sprite.setTextureRect(
            sf::IntRect(0, 0, MAP_BLOCK_SIZE / 2, MAP_BLOCK_SIZE / 2));
        wall_sprite.setScale(2, 2);

        window->draw(wall_sprite);
      }
      if (map[col][row] == Block::Column) {
        column_sprite.setPosition(MAP_BLOCK_SIZE * row, MAP_BLOCK_SIZE * col);
        column_sprite.setTextureRect(
            sf::IntRect(0, 0, MAP_BLOCK_SIZE / 2, MAP_BLOCK_SIZE / 2));
        column_sprite.setScale(2, 2);

        window->draw(column_sprite);
      }
      if (map[col][row] == Block::Door) {
        door_sprite.setPosition(MAP_BLOCK_SIZE * row, MAP_BLOCK_SIZE * col);
        door_sprite.setTextureRect(
            sf::IntRect(0, 0, MAP_BLOCK_SIZE / 2, MAP_BLOCK_SIZE / 2));
        door_sprite.setScale(2, 2);

        window->draw(door_sprite);
      }
    }
  }
}

Block Map::getWall(int x, int y) { return map[y][x]; }

bool Map::checkIfWall(float x, float y, float block_size) {
  int pos_x = x / block_size;
  int pos_y = y / block_size;

  if (map[pos_y][pos_x] != Block::Empty &&
      map[pos_y][pos_x] != Block::IPlayer) {
    return true;
  }

  return false;
}
