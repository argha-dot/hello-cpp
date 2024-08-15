#include <SFML/Window/Keyboard.hpp>
#include <cmath>
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

  position = sf::Vector2<float>(60, 60);
  direction = sf::Vector2<float>(0, -1);
  plane = sf::Vector2<float>(0, 0.66);
  size = texture.getSize().y;
}

void Player::draw(sf::RenderWindow *window) {
  sprite.setPosition(position.x, position.y);
  sprite.setRotation(90 + rad_to_deg(std::atan2(direction.y, direction.x)));
  sprite.setOrigin(size / 2, size / 2);

  sprite.setTextureRect(sf::IntRect(0, 0, size, size));

  window->draw(sprite);
}

void Player::update(sf::RenderWindow *window, Map *map, float *dt) {
  float rotationSpeed = PLAYER_ROTATION_SPEED * *dt;
  float movementSpeed = PLAYER_MOVEMENT_SPEED * *dt;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    sf::Vector2<float> oldDirection{direction};
    sf::Vector2<float> oldPlane{plane};

    direction.x =
        direction.x * cos(-rotationSpeed) - direction.y * sin(-rotationSpeed);
    direction.y = oldDirection.x * sin(-rotationSpeed) +
                  direction.y * cos(-rotationSpeed);

    plane.x = plane.x * cos(-rotationSpeed) - plane.y * sin(-rotationSpeed);
    plane.y = oldPlane.x * sin(-rotationSpeed) + plane.y * cos(-rotationSpeed);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    sf::Vector2<float> oldDirection = direction;
    sf::Vector2<float> oldPlane{plane};

    direction.x =
        direction.x * cos(rotationSpeed) - direction.y * sin(rotationSpeed);
    direction.y =
        oldDirection.x * sin(rotationSpeed) + direction.y * cos(rotationSpeed);

    plane.x = plane.x * cos(rotationSpeed) - plane.y * sin(rotationSpeed);
    plane.y = oldPlane.x * sin(rotationSpeed) + plane.y * cos(rotationSpeed);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

    float dx = movementSpeed * direction.x;
    float dy = movementSpeed * direction.y;

    if (!map->check_if_wall(position.x + dx, position.y)) {
      position.x += movementSpeed * direction.x;
    }

    if (!map->check_if_wall(position.x, position.y + dy)) {
      position.y += movementSpeed * direction.y;
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    float dx = movementSpeed * direction.x;
    float dy = movementSpeed * direction.y;

    if (!map->check_if_wall(position.x - dx, position.y)) {
      position.x -= movementSpeed * direction.x;
    }

    if (!map->check_if_wall(position.x, position.y - dy)) {
      position.y -= movementSpeed * direction.y;
    }
  }
}

void Player::setPosition(float new_x, float new_y) {
  position.x = new_x;
  position.y = new_y;
}
