#include <cmath>
// #include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "headers/globals.h"
#include "headers/map.h"
#include "headers/player.h"

void Player::renderFloor(sf::RenderWindow *window, sf::Image *windowImage) {
  sf::Image floor_image;
  floor_image.loadFromFile("src/assets/images/brickwall.png");

  for (int stripe = 0; stripe < SCREEN_HEIGHT; stripe++) {
    sf::Vector2f rayDirLeft(direction.x - plane.x, direction.y - plane.y);
    sf::Vector2f rayDirRight(direction.x + plane.x, direction.y + plane.y);

    int p = stripe - SCREEN_HEIGHT * 0.5f;
    float cameraHeight = SCREEN_HEIGHT * CAMERA_HEIGHT;

    float rowDistance = cameraHeight / p;

    sf::Vector2f floorStep(
        rowDistance * (rayDirRight.x - rayDirLeft.x) / SCREEN_WIDTH,
        rowDistance * (rayDirRight.y - rayDirLeft.y) / SCREEN_WIDTH);

    sf::Vector2f floorPos(position.x + rayDirLeft.x * rowDistance,
                          position.y + rayDirLeft.y * rowDistance);

    for (int ray = 0; ray < SCREEN_WIDTH; ray++) {
      sf::Vector2i cell((int)floorPos.x, (int)floorPos.y);
      sf::Vector2i textureCoord(
          static_cast<int>(TEXTURE_WIDTH * (floorPos.x - cell.x)) &
              (TEXTURE_WIDTH - 1),
          static_cast<int>(TEXTURE_HEIGHT * (floorPos.y - cell.y)) &
              (TEXTURE_HEIGHT - 1));

      floorPos.x += floorStep.x;
      floorPos.y += floorStep.y;

      sf::Color floor_image_pixel =
          floor_image.getPixel(textureCoord.x, textureCoord.y);

      floor_image_pixel.g /= 3;
      windowImage->setPixel(ray, SCREEN_HEIGHT - stripe - 1, floor_image_pixel);

      floor_image_pixel.r /= 3;

      windowImage->setPixel(ray, stripe, floor_image_pixel);
    }
  }
}

void Player::rayCast(Map *map, sf::Texture *texture, sf::Image *windowImage) {
  sf::Image wall_image;
  wall_image.loadFromFile("src/assets/images/brickwall.png");

  for (int ray = 0; ray < SCREEN_WIDTH; ray++) {
    float cameraX = 2.0 * ray / SCREEN_WIDTH - 1;

    sf::Vector2f rayDirection(direction.x + plane.x * cameraX,
                              direction.y + plane.y * cameraX);

    sf::Vector2f mapPosition(int(position.x), int(position.y));

    sf::Vector2f sideDistance;

    sf::Vector2f deltaDistance(
        (rayDirection.x == 0) ? 1e30 : std::abs(1 / rayDirection.x),
        (rayDirection.y == 0) ? 1e30 : std::abs(1 / rayDirection.y));

    float perpendicularWallDistance = 0.0;

    sf::Vector2i step = sf::Vector2i(0, 0);

    Block hit = Block::Empty; // Was a wall hit?
    int side = 0;             // Which side of the wall was hit?

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

    while (hit == Block::Empty) {
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
        hit = map->getWall(mapPosition.x, mapPosition.y, 1);
      }
    }

    if (side == 0) {
      perpendicularWallDistance = (sideDistance.x - deltaDistance.x);
    } else {
      perpendicularWallDistance = (sideDistance.y - deltaDistance.y);
    }

    int lineHeight = (int)(SCREEN_HEIGHT / perpendicularWallDistance);
    // int drawStart = static_cast<int>(-lineHeight * (1. - CAMERA_HEIGHT) +
    //                                  SCREEN_HEIGHT * 0.5f);
    int drawStart = static_cast<int>(-lineHeight * 0.5f + SCREEN_HEIGHT * 0.5f);

    int drawEnd = static_cast<int>(lineHeight * 0.5f + SCREEN_HEIGHT * 0.5f);

    if (drawStart < 0) {
      drawStart = 0;
    }

    if (drawEnd >= SCREEN_HEIGHT) {
      drawEnd = SCREEN_HEIGHT - 1;
    }

    float wallX = 0.0;
    if (side == 0) {
      wallX = position.y + rayDirection.y * perpendicularWallDistance;
    } else {
      wallX = position.x + rayDirection.x * perpendicularWallDistance;
    }

    wallX -= std::floor(wallX);

    int texX = int(wallX * float(TEXTURE_WIDTH));
    // if ((side == 1 && rayDirection.x < 0) ||
    //     (side == 0 && rayDirection.y > 0)) {
    //   texX = TEXTURE_WIDTH - texX - 1;
    // }

    float stepSize = 1. * TEXTURE_WIDTH / lineHeight;
    float texPos =
        (drawStart - float(SCREEN_HEIGHT) / 2 + float(lineHeight) / 2) *
        stepSize;

    for (int y = drawStart; y < drawEnd; y++) {
      int texY = static_cast<int>(texPos) & (TEXTURE_HEIGHT - 1);
      texPos += stepSize;
      sf::Color color = wall_image.getPixel(texX, texY);
      // sf::Color color = sf::Color::White;
      if (side == 1) {
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
      }

      switch (hit) {
      case Block::Column:
        color.r /= 3;
        break;
      case Block::Wall:
      default:
        break;
      }

      windowImage->setPixel(ray, y, color);
    }
  }
}
