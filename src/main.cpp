#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <array>

import grid;
import blocks;

constexpr int gridWidthInCells = 10;
constexpr int gridHeightInCells = 30;

bool canMove(const blocks::Blocks& blocks, const int dx, const int dy, const int cellSize) {
    for (const auto& block : blocks.getBlocks()) {
        sf::Vector2f futurePosition = block.getPosition() + sf::Vector2f(dx * cellSize, dy * cellSize);
        if (futurePosition.x < 0 || futurePosition.x >= gridWidthInCells * cellSize ||
            futurePosition.y >= gridHeightInCells * cellSize) {
            return false;
            }
    }
    return true;
}

int main()
{
    constexpr int windowWidth = 600;
    constexpr int windowHeight = 900;
    constexpr int cellSize = 60;

    sf::RenderWindow window({windowWidth, windowHeight}, "Tetris");
    window.setFramerateLimit(60);

    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("C:/Esimed admin/C++/TetrisC/assets/tiles.png")) {
        throw std::runtime_error("Unable to load texture from file!");
    }

    blocks::Blocks yellowBlocks(cellSize, tileTexture, 0);

    grid::Grid grid(windowWidth, windowHeight, cellSize);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (canMove(yellowBlocks, -1, 0, cellSize)) {
                yellowBlocks.move(-1, 0);
                sf::sleep(sf::milliseconds(150));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (canMove(yellowBlocks, 1, 0, cellSize)) {
                yellowBlocks.move(1, 0);
                sf::sleep(sf::milliseconds(150));
            }
        }

        if (clock.getElapsedTime().asSeconds() > 1) {
            if (canMove(yellowBlocks, 0, 1, cellSize)) {
                yellowBlocks.move(0, 1);
            }
            clock.restart();
        }

        window.clear();
        grid.draw(window);
        yellowBlocks.draw(window);
        window.display();
    }

    return 0;
}
