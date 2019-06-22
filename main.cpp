#include <SFML/Graphics.hpp>
#include <iostream>

bool isInsideGrid(sf::Vector2f&& nextPosition, float width, float height) {
  return (nextPosition.x > 0 && nextPosition.x < width && nextPosition.y > 0 &&
          nextPosition.y < height);
}

void updatePlayerSprite(sf::Sprite& sprite, unsigned rowIdx, unsigned colIdx, unsigned offset) {
  int startX = colIdx * offset;
  int startY = rowIdx * offset;

  sprite.setTextureRect(sf::IntRect(startX, startY, offset, offset));
}

int main() {
  unsigned length = 800;
  unsigned offset = 64;
  sf::RenderWindow window(sf::VideoMode(length, length), "Sokoban-Clone");
  float gridLength = length - offset;
  auto speed = 10.0f;

  window.setFramerateLimit(60);
  sf::Clock clock;  // starts the clock

  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites.png")) {
    return -1;
  }

  sf::Sprite player;
  player.setTexture(texture);

  updatePlayerSprite(player, 4, 0, offset);
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
            updatePlayerSprite(player, 6, 3 + counter, offset);
            currentPlayerDirection = sf::Vector2f(-1, 0);
          }
          if (event.key.code == sf::Keyboard::D) {
            updatePlayerSprite(player, 6, 0 + counter, offset);
            currentPlayerDirection = sf::Vector2f(1, 0);
          }
          if (event.key.code == sf::Keyboard::W) {
            updatePlayerSprite(player, 4, 3 + counter, offset);
            currentPlayerDirection = sf::Vector2f(0, -1);
          }
          if (event.key.code == sf::Keyboard::S) {
            updatePlayerSprite(player, 4, 0 + counter, offset);
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

    window.clear();
    window.draw(player);
    window.display();

    auto displacement = speed * currentPlayerDirection;
    if (isInsideGrid(currentPlayerPosition + displacement, gridLength, gridLength)) {
      currentPlayerPosition += displacement;
      player.setPosition(currentPlayerPosition.x, currentPlayerPosition.y);
    }

    std::cout << "location: " << (int)currentPlayerPosition.x << ", "
              << (int)currentPlayerPosition.y << std::endl;

    // reset player direction
    currentPlayerDirection = sf::Vector2f(0, 0);
  }

  return 0;
}
