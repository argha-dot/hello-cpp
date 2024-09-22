#include <cmath>

#include <SFML/Graphics/RenderWindow.hpp>

#include "headers/game.h"
#include "headers/globals.h"
#include "headers/map.h"
#include "headers/player.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hello CPP",
             sf::Style::Default, settings),
      player(map.getPlayerPosition(1)), lines(sf::Lines, 18 * SCREEN_WIDTH) {

  textureImage.loadFromFile("src/assets/images/brickwall.png");

  windowSprite.setPosition(0, 0);

  windowImage.create(SCREEN_WIDTH, SCREEN_HEIGHT);

  settings = window.getSettings();
  settings.antialiasingLevel = 8;

  window.setVerticalSyncEnabled(true);
  window.setMouseCursorVisible(false);
  window.setActive(true);

  Map map{};
}

void Game::updateDelta() {
  dt = clock.restart().asSeconds();
  window.setTitle("fps: " + std::to_string(static_cast<int>(1 / dt)));
}

void Game::draw() {
  // window.clear(BG_DARK_COLOR);

  // player.renderFloor(&window, &textureImage, &windowImage);
  player.rayCast(&map, &textureImage, &windowImage);
  window.clear(BG_DARK_COLOR);

  windowTexture.loadFromImage(windowImage);
  windowSprite.setTexture(windowTexture);
  windowSprite.setScale(static_cast<float>(WINDOW_WIDTH) / SCREEN_WIDTH,
                        static_cast<float>(WINDOW_HEIGHT) / SCREEN_HEIGHT);

  window.draw(windowSprite);

  window.display();
}

void Game::handleEvents() {
  sf::Event event;

  while (window.pollEvent(event)) {
    if (window.hasFocus() &&
        (event.type == sf::Event::Closed ||
         sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) {
      window.close();
    }
  }
  lines.resize(0);
}

void Game::update() {
  updateDelta();
  if (window.hasFocus()) {
    player.update(&window, &map, &dt);
  }
}

void Game::run() {
  while (window.isOpen()) {
    handleEvents();
    update();
    draw();
  }
}

Game::~Game() {}
