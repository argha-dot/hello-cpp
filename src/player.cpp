#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>

#include "headers/globals.h"
#include "headers/map.h"
#include "headers/player.h"
#include "headers/utils.h"

Player::Player(float x, float y) : sprite(texture) {
  if (!texture.loadFromFile("src/assets/images/player.png")) {
    std::cerr << "Couldn't load image";
  }

  sprite.setScale(MAP_BLOCK_SIZE, MAP_BLOCK_SIZE);
  size = texture.getSize().y;

  position = sf::Vector2<float>(x, y);

  plane = sf::Vector2<float>(0, 0.66);
  direction = sf::Vector2<float>(-1, 0);
}

Player::Player(sf::Vector2<float> initPos)
    : position(initPos), sprite(texture) {
  if (!texture.loadFromFile("src/assets/images/player.png")) {
    std::cerr << "Couldn't load image";
  }

  sprite.setScale(1. / 3, 1. / 3);
  direction = sf::Vector2<float>(-1, 0);
  plane = sf::Vector2<float>(0, 0.66);
  size = texture.getSize().y;
}

void Player::draw(sf::RenderWindow *window) {
  sprite.setPosition(position.x * MAP_BLOCK_SIZE, position.y * MAP_BLOCK_SIZE);
  sprite.setRotation(90 + rad_to_deg(std::atan2(direction.y, direction.x)));
  sprite.setOrigin(size / 2, size / 2);

  sprite.setTextureRect(sf::IntRect(0, 0, size, size));

  window->draw(sprite);
}

void Player::handleMouse(sf::Window *window, float *dt) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
  unsigned int windowCenterX = WINDOW_WIDTH / 2;

  float roatationX = (static_cast<float>(windowCenterX) - mousePos.x) /
                     WINDOW_WIDTH * *dt * MOUSE_SENSITIVITY;
  rotatePlayer(roatationX);

  sf::Mouse::setPosition(sf::Vector2i(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
                         *window);
}

void Player::rotatePlayer(float rotationSpeed) {
  sf::Vector2<float> oldDirection = direction;
  sf::Vector2<float> oldPlane = plane;

  direction.x =
      direction.x * cos(rotationSpeed) - direction.y * sin(rotationSpeed);
  direction.y =
      oldDirection.x * sin(rotationSpeed) + direction.y * cos(rotationSpeed);

  plane.x = plane.x * cos(rotationSpeed) - plane.y * sin(rotationSpeed);
  plane.y = oldPlane.x * sin(rotationSpeed) + plane.y * cos(rotationSpeed);
}

void Player::update(sf::RenderWindow *window, Map *map, float *dt) {
  float movementSpeed = PLAYER_MOVEMENT_SPEED * *dt;

  handleMouse(window, dt);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    float dx = (plane.x > 0) ? movementSpeed * direction.x + 0.5f
                             : movementSpeed * plane.x - 0.5f;
    float dy = (plane.y < 0) ? movementSpeed * direction.y - 0.5f
                             : movementSpeed * plane.y + 0.5f;

    if (!map->checkIfWall(position.x - dx, position.y, 1)) {
      position.x -= movementSpeed * plane.x;
    }

    if (!map->checkIfWall(position.x, position.y - dy, 1)) {
      position.y -= movementSpeed * plane.y;
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    float dx = (plane.x > 0) ? movementSpeed * plane.x + 0.5f
                             : movementSpeed * plane.x - 0.5f;
    float dy = (plane.y < 0) ? movementSpeed * plane.y - 0.5f
                             : movementSpeed * plane.y + 0.5f;

    if (!map->checkIfWall(position.x + dx, position.y, 1)) {
      position.x += movementSpeed * plane.x;
    }

    if (!map->checkIfWall(position.x, position.y + dy, 1)) {
      position.y += movementSpeed * plane.y;
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    float dx = (direction.x > 0) ? movementSpeed * direction.x + 0.5f
                                 : movementSpeed * direction.x - 0.5f;
    float dy = (direction.y < 0) ? movementSpeed * direction.y - 0.5f
                                 : movementSpeed * direction.y + 0.5f;

    if (!map->checkIfWall(position.x + dx, position.y, 1)) {
      position.x += movementSpeed * direction.x;
    }

    if (!map->checkIfWall(position.x, position.y + dy, 1)) {
      position.y += movementSpeed * direction.y;
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    float dx = (direction.x > 0) ? movementSpeed * direction.x + 0.5f
                                 : movementSpeed * direction.x - 0.5f;
    float dy = (direction.y < 0) ? movementSpeed * direction.y - 0.5f
                                 : movementSpeed * direction.y + 0.5f;

    if (!map->checkIfWall(position.x - dx, position.y, 1)) {
      position.x -= movementSpeed * direction.x;
    }

    if (!map->checkIfWall(position.x, position.y - dy, 1)) {
      position.y -= movementSpeed * direction.y;
    }
  }
}

void Player::setPosition(float new_x, float new_y) {
  position.x = new_x;
  position.y = new_y;
}
