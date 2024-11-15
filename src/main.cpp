#include <SFML/Graphics.hpp>
#include <stdexcept>

import grid;
import blocks;

int main()
{
    constexpr int windowWidth = 600;
    constexpr int windowHeight = 900;
    constexpr int cellSize = 60;

    sf::RenderWindow window({windowWidth, windowHeight}, "Tetris");
    window.setFramerateLimit(144);

    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("C:/Esimed admin/C++/TetrisC/assets/tiles.png")) {
        throw std::runtime_error("Unable to load texture from file!");
    }

    blocks::Blocks yellowTetromino(cellSize, tileTexture, 0);

    grid::Grid grid(windowWidth, windowHeight, cellSize);

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        grid.draw(window);
        yellowTetromino.draw(window);
        window.display();
    }

    return 0;
}
