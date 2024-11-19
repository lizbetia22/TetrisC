#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <cstdlib>

import grid;
import blocks;
import blocksController;
import songController;

int main()
{
    constexpr int windowWidth = 600;
    constexpr int windowHeight = 900;
    constexpr int cellSize = 60;

    constexpr int gridWidthInCells = windowWidth / cellSize;
    constexpr int gridHeightInCells = windowHeight / cellSize;

    sf::RenderWindow window({windowWidth, windowHeight}, "Tetris");
    window.setFramerateLimit(60);

    songController::SongPlayer songPlayer;
    try {
        songPlayer.loadBackgroundMusic("assets/songs/tetris_classic_song.wav");
        songPlayer.setBackgroundVolume(50.0f);
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Unable to load song from file!");
    }

    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("assets/images/tiles.png")) {
        throw std::runtime_error("Unable to load texture from file!");
    }

    int shapeType = std::rand() % 7;
    blocks::Blocks randomBlock(cellSize, tileTexture, shapeType);

    grid::Grid grid(windowWidth, windowHeight, cellSize);

    blocksController::BlocksController controller(gridWidthInCells, gridHeightInCells, cellSize, tileTexture, songPlayer);

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                songPlayer.stop();
                window.close();
            }
        }

        float deltaTime = deltaClock.restart().asSeconds();

        controller.handleInput();

        controller.update(deltaTime);

        window.clear();
        grid.draw(window);
        controller.draw(window);
        window.display();
    }

    return 0;
}
