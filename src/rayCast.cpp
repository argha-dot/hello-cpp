#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "headers/map.h"
#include "headers/player.h"

void Player::traditionalRayCast(Map *map, sf::RenderWindow *window) {}

void Player::borkedRayCast(Map *map, sf::RenderWindow *window) {
  for (int ray = 0; ray < WINDOW_WIDTH; ray++) {
    float cameraX = 2.0 * ray / WINDOW_WIDTH - 1;

    sf::Vector2<float> rayDirection(direction.x + plane.x * cameraX,
                                    direction.y + plane.y * cameraX);

    sf::Vector2<float> mapPosition(int(position.x), int(position.y));

    sf::Vector2<float> sideDistance;

    sf::Vector2<float> deltaDistance(
        (rayDirection.x == 0) ? 1e30 : std::abs(1 / rayDirection.x),
        (rayDirection.y == 0) ? 1e30 : std::abs(1 / rayDirection.y));

    float perpendicularWallDistance;

    sf::Vector2<int> step;

    bool hit = false; // Was a wall hit?
    int side;         // Which side of the wall was hit?

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

    while (!hit) {
      if (sideDistance.x < sideDistance.y) {
        sideDistance.x += deltaDistance.x;
        mapPosition.x += step.x;
        side = 0;
      } else {
        sideDistance.y += deltaDistance.y;
        mapPosition.y += step.y;
        side = 1;
      }

      if (map->check_if_wall(mapPosition.x, mapPosition.y, 1)) {
        hit = true;
      }
    }

    if (side == 0) {
      perpendicularWallDistance = (sideDistance.x - deltaDistance.x);
    } else {
      perpendicularWallDistance = (sideDistance.y - deltaDistance.y);
    }

    int lineHeight = (int)(WINDOW_HEIGHT / perpendicularWallDistance);
    int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
    if (drawStart < 0) {
      drawStart = 0;
    }

    int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
    if (drawEnd >= WINDOW_HEIGHT) {
      drawEnd = WINDOW_HEIGHT - 1;
    }

    sf::Color color;

    switch (map->getWall(mapPosition.x, mapPosition.y)) {
    case Block::Wall:
      color = sf::Color::Red;
      break;
    case Block::IPlayer:
      break;
    default:
      color = sf::Color::Yellow;
      break;
    }

    if (side == 1) {
      color.r /= 2;
      color.g /= 2;
      color.b /= 2;
    }

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(ray, drawStart), color),
        sf::Vertex(sf::Vector2f(ray, drawEnd), color),
    };

    window->draw(line, 2, sf::Lines);
  }
}
