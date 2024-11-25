#include <SFML/Graphics.hpp>
#include <stdexcept>

import grid;
import blocks;
import sidebar;
import blocksController;
import songController;

int main()
{
    constexpr int cellSize = 60;
    constexpr int gridWidth = 10;
    constexpr int gridHeight = 15;

    constexpr int windowWidth = gridWidth * cellSize;
    constexpr int windowHeight = gridHeight * cellSize;
    constexpr int sidebarWidth = 300;

    sf::RenderWindow window({windowWidth + sidebarWidth, windowHeight}, "Tetris by Eliza Bet");
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

    grid::Grid grid(windowWidth, windowHeight, cellSize);
    sidebar::Sidebar sidebar(windowWidth + sidebarWidth, windowHeight, gridWidth);

    blocksController::BlocksController controller(gridWidth, gridHeight, cellSize, tileTexture, songPlayer);

    sf::RectangleShape pauseOverlay;
    pauseOverlay.setSize(sf::Vector2f(windowWidth, windowHeight));
    pauseOverlay.setFillColor(sf::Color(150, 150, 150, 150));

    sf::RectangleShape gameOverOverlay;
    gameOverOverlay.setSize(sf::Vector2f(windowWidth, windowHeight));
    gameOverOverlay.setFillColor(sf::Color(150, 150, 150, 150));

    sf::Clock deltaClock;
    int score = 0;
    bool isPaused = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                songPlayer.stop();
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (sidebar.isPauseClicked(mousePos)) {
                    isPaused = !isPaused;
                    if (isPaused) {
                        songPlayer.pause();
                    } else {
                        songPlayer.resume();
                    }
                }

                if (sidebar.isRestartClicked(mousePos)) {
                    score = 0;
                    sidebar.updateScore(score);
                    sidebar.showGameOver(false);
                    controller.resetGame();
                    songPlayer.stop();
                    songPlayer.loadBackgroundMusic("assets/songs/tetris_classic_song.wav");
                }

                if (sidebar.isCloseClicked(mousePos)) {
                    songPlayer.stop();
                    window.close();
                }
            }
        }

        if (!isPaused && !controller.isGameOver()) {
            float deltaTime = deltaClock.restart().asSeconds();

            controller.handleInput();
            controller.update(deltaTime);

            int linesCleared = controller.checkAndClearLines();
            if (linesCleared > 0) {
                score += linesCleared * 10;
                sidebar.updateScore(score);
                controller.updateFallSpeed(score);
            }
            if (controller.isGameOver()) {
                sidebar.showGameOver(true);
                songPlayer.stop();
                songPlayer.playGameOverSound("assets/songs/game_over_sound.wav");
            }
            if (auto nextBlock = controller.getNextBlock()) {
                sidebar.updateNextBlock(std::move(nextBlock));
            }
        }

        window.clear();
        grid.draw(window);
        controller.draw(window);
        sidebar.draw(window);
        if (isPaused) {
            window.draw(pauseOverlay);
        }
        if (controller.isGameOver()) {
            window.draw(gameOverOverlay);
        }
        window.display();
    }

    return 0;
}