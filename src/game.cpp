#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "headers/game.h"
#include "headers/globals.h"
#include "headers/map.h"
#include "headers/player.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hello CPP",
             sf::Style::Default, settings),
      floor(sf::Vector2f(WINDOW_WIDTH, static_cast<float>(WINDOW_HEIGHT) / 2)),
      player(map.getPlayerPosition(1)), lines(sf::Lines, 18 * WINDOW_WIDTH) {

  if (!textureMap.loadFromFile("src/assets/images/brickwall.png")) {
    // if (!textureMap.loadFromFile("src/assets/images/some.png")) {
    std::cerr << "Error Opening Texture" << std::endl;
  }

  state.texture = &textureMap;
  settings = window.getSettings();
  settings.antialiasingLevel = 8;

  window.setVerticalSyncEnabled(true);
  window.setMouseCursorVisible(false);
  window.setActive(true);

  floor.setFillColor(BG_LIGHT_COLOR);

  Map map{};
}

void Game::updateDelta() {
  dt = clock.restart().asSeconds();
  window.setTitle("fps: " + std::to_string(1 / dt));
}

void Game::draw() {
  window.clear(BG_DARK_COLOR);

  window.draw(floor);
  player.renderFloor(&window, &lines, &textureMap, &state);
  player.rayCast(&map, &window, &lines, &textureMap, &state);
  map.draw(&window);
  player.draw(&window);

  window.display();
}

void Game::handleEvents() {
  sf::Event event;

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      window.close();
    }
  }
  lines.resize(0);
}

void Game::update() {
  updateDelta();
  player.update(&window, &map, &dt);
}

void Game::run() {
  while (window.isOpen()) {
    handleEvents();
    update();
    draw();
  }
}

Game::~Game() {}
