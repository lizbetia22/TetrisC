#include <SFML/Graphics.hpp>
#include <stdexcept>

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

    blocks::Blocks yellowBlocks(cellSize, tileTexture, 0);

    grid::Grid grid(windowWidth, windowHeight, cellSize);

    movements::Movements controller(yellowBlocks, gridWidthInCells, gridHeightInCells, cellSize);

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
        yellowBlocks.draw(window);
        window.display();
    }

    return 0;
}
