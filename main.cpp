#include <SFML/Graphics.hpp>
#include <iostream>

bool isInsideGrid(sf::Sprite& player) {
  auto pos = player.getPosition();
  return pos.x >= 0 && pos.x < 768 && pos.y > 32 && pos.y < 768;
}

void updatePlayerSprite(sf::Sprite& sprite, unsigned rowIdx, unsigned colIdx) {
  int offset = 64;
  int startX = colIdx * offset;
  int startY = rowIdx * offset;

  sprite.setTextureRect(sf::IntRect(startX, startY, offset, offset));
}

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "Sokoban-Clone");
  auto speed = 10.0f;

  window.setFramerateLimit(60);
  sf::Clock clock;  // starts the clock

  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites.png")) {
    return -1;
  }

  sf::Sprite player;
  player.setTexture(texture);

  updatePlayerSprite(player, 4, 0);
  player.move(500, 600);
  sf::Vector2f currentPlayerPosition(500, 500);
  sf::Vector2f currentPlayerDirection(0, 0);

  window.draw(player);
  unsigned counter = 0;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::A) {
            updatePlayerSprite(player, 6, 3 + counter);
            currentPlayerDirection = sf::Vector2f(-1, 0);
          }
          if (event.key.code == sf::Keyboard::D) {
            updatePlayerSprite(player, 6, 0 + counter);
            currentPlayerDirection = sf::Vector2f(1, 0);
          }
          if (event.key.code == sf::Keyboard::W) {
            updatePlayerSprite(player, 4, 3 + counter);
            currentPlayerDirection = sf::Vector2f(0, -1);
          }
          if (event.key.code == sf::Keyboard::S) {
            updatePlayerSprite(player, 4, 0 + counter);
            currentPlayerDirection = sf::Vector2f(0, 1);
          }

          counter = (counter + 1) % 3;

        default:
          break;
      }
    }

    sf::Time timeElapsed = clock.getElapsedTime();
    float fps = 1.f / timeElapsed.asSeconds();
    std::cout << "FPS: " << fps << std::endl;
    clock.restart();

    std::cout << (int)currentPlayerPosition.x << ", " << (int)currentPlayerPosition.y << std::endl;

    window.clear();
    window.draw(player);
    window.display();

    currentPlayerPosition += speed * currentPlayerDirection;
    currentPlayerDirection = sf::Vector2f(0, 0);
    player.setPosition(currentPlayerPosition.x, currentPlayerPosition.y);
  }

  return 0;
}
