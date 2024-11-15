#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <cstdlib>

import grid;
import blocks;
import movements;

int main()
{
    constexpr int windowWidth = 600;
    constexpr int windowHeight = 900;
    constexpr int cellSize = 60;

    constexpr int gridWidthInCells = windowWidth / cellSize;
    constexpr int gridHeightInCells = windowHeight / cellSize;

    sf::RenderWindow window({windowWidth, windowHeight}, "Tetris");
    window.setFramerateLimit(60);

    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("C:/Esimed admin/C++/TetrisC/assets/tiles.png")) {
        throw std::runtime_error("Unable to load texture from file!");
    }

    int shapeType = std::rand() % 7;
    blocks::Blocks randomBlock(cellSize, tileTexture, shapeType);

    grid::Grid grid(windowWidth, windowHeight, cellSize);

    movements::Movements controller(randomBlock, gridWidthInCells, gridHeightInCells, cellSize);

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = deltaClock.restart().asSeconds();

        controller.handleInput();

        controller.update(deltaTime);

        window.clear();
        grid.draw(window);
        randomBlock.draw(window);
        window.display();
    }

    return 0;
}
