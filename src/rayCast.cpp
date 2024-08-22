#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "headers/globals.h"
#include "headers/map.h"
#include "headers/player.h"

void Player::rayCast(Map *map, sf::RenderWindow *window, sf::VertexArray *lines,
                     sf::Texture *texture, sf::RenderStates *state) {

  for (int ray = 0; ray < WINDOW_WIDTH; ray++) {
    float cameraX = 2.0 * ray / WINDOW_WIDTH - 1;

    sf::Vector2<float> rayDirection(direction.x + plane.x * cameraX,
                                    direction.y + plane.y * cameraX);

    sf::Vector2<float> mapPosition(int(position.x), int(position.y));

    sf::Vector2<float> sideDistance;

    sf::Vector2<float> deltaDistance(
        (rayDirection.x == 0) ? 1e30 : std::abs(1 / rayDirection.x),
        (rayDirection.y == 0) ? 1e30 : std::abs(1 / rayDirection.y));

    float perpendicularWallDistance = 0.0;

    sf::Vector2<int> step = sf::Vector2<int>(0, 0);

    int hit = 0;  // Was a wall hit?
    int side = 0; // Which side of the wall was hit?

    if (rayDirection.x < 0) {
      step.x = -1;
      sideDistance.x = (position.x - mapPosition.x) * deltaDistance.x;
    } else {
      step.x = 1;
      sideDistance.x = (mapPosition.x + 1.0 - position.x) * deltaDistance.x;
    }

    if (rayDirection.y < 0) {
      step.y = -1;
      sideDistance.y = (position.y - mapPosition.y) * deltaDistance.y;
    } else {
      step.y = 1;
      sideDistance.y = (mapPosition.y + 1.0 - position.y) * deltaDistance.y;
    }

    while (hit == 0) {
      if (sideDistance.x < sideDistance.y) {
        sideDistance.x += deltaDistance.x;
        mapPosition.x += step.x;
        side = 0;
      } else {
        sideDistance.y += deltaDistance.y;
        mapPosition.y += step.y;
        side = 1;
      }

      if (map->checkIfWall(mapPosition.x, mapPosition.y, 1)) {
        hit = 1;
      }
    }

    if (side == 0) {
      perpendicularWallDistance = (sideDistance.x - deltaDistance.x);
    } else {
      perpendicularWallDistance = (sideDistance.y - deltaDistance.y);
    }

    int lineHeight = (int)(WINDOW_HEIGHT / perpendicularWallDistance);
    int drawStart = static_cast<int>(-lineHeight * (1. - CAMERA_HEIGHT) +
                                     WINDOW_HEIGHT * 0.5f);

    int drawEnd =
        static_cast<int>(lineHeight * CAMERA_HEIGHT + WINDOW_HEIGHT * 0.5f);

    float wallX = 0.0;
    if (side == 0) {
      wallX = position.y + rayDirection.y * perpendicularWallDistance;
    } else {
      wallX = position.x + rayDirection.x * perpendicularWallDistance;
    }

    wallX -= std::floor(wallX);

    int texX = int(wallX * float(TEXTURE_WIDTH));
    if ((side == 1 && rayDirection.x <= 0) ||
        (side == 0 && rayDirection.y >= 0)) {
      texX = TEXTURE_WIDTH - texX - 1;
    }

    sf::Color color{sf::Color::White};

    if (side == 1) {
      color.r /= 2;
      color.g /= 2;
      color.b /= 2;
    }

    lines->append(sf::Vertex(
        sf::Vector2f(static_cast<float>(ray), static_cast<float>(drawStart)),
        color, sf::Vector2f(texX, 0)));
    lines->append(sf::Vertex(
        sf::Vector2f(static_cast<float>(ray), static_cast<float>(drawEnd)),
        color, sf::Vector2f(texX, TEXTURE_HEIGHT - 1)));
  }
  window->draw(*lines, *state);
}
