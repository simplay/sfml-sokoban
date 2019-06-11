#include <SFML/Graphics.hpp>
#include <iostream>

void updatePlayerSprite(sf::Sprite& sprite, unsigned rowIdx, unsigned colIdx) {
  int offset = 64;
  int startX = colIdx * offset;
  int startY = rowIdx * offset;

  sprite.setTextureRect(sf::IntRect(startX, startY, offset, offset));
}

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "Sokoban-Clone");
  auto speed = 10.0f;

  window.setFramerateLimit(60);
  sf::Clock clock;  // starts the clock

  float fps = 0;

  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites.png")) {
    return -1;
  }

  sf::Sprite player;
  player.setTexture(texture);

  updatePlayerSprite(player, 4, 0);
  player.move(500, 600);
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
            player.move(-speed, 0);
            updatePlayerSprite(player, 6, 3 + counter);
          }
          if (event.key.code == sf::Keyboard::D) {
            player.move(speed, 0);
            updatePlayerSprite(player, 6, 0 + counter);
          }
          if (event.key.code == sf::Keyboard::W) {
            player.move(0, -speed);
            updatePlayerSprite(player, 4, 3 + counter);
          }
          if (event.key.code == sf::Keyboard::S) {
            player.move(0, speed);
            updatePlayerSprite(player, 4, 0 + counter);
          }

          counter = (counter + 1) % 3;

        default:
          break;
      }
    }

    sf::Time timeElapsed = clock.getElapsedTime();
    fps = 1.f / timeElapsed.asSeconds();
    std::cout << "FPS: " << fps << std::endl;
    clock.restart();

    auto position = player.getPosition();
    std::cout << (int)position.x << ", " << (int)position.y << std::endl;

    window.clear();
    window.draw(player);
    window.display();
  }

  return 0;
}
