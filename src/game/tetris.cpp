module;

#include <SFML/Graphics.hpp>

module tetris;

namespace tetris {
    Game::Game()
     : m_window({900, 900}, "Tetris by Eliza Bet"),
       m_grid(600, 900, 60),
       m_sidebar(900, 900, 10),
       m_controller(10, 15, 60, m_tileTexture, m_songPlayer)
    {

        m_window.setFramerateLimit(60);

        if (!m_tileTexture.loadFromFile("assets/images/tiles.png")) {
            throw std::runtime_error("Unable to load texture!");
        }

        try {
            m_songPlayer.loadBackgroundMusic("assets/songs/tetris_classic_song.wav");
            m_songPlayer.setBackgroundVolume(50.0f);
        } catch (const std::runtime_error& e) {
            throw std::runtime_error("Unable to load song!");
        }

        m_pauseOverlay.setSize(sf::Vector2f(600, 900));
        m_pauseOverlay.setFillColor(sf::Color(150, 150, 150, 150));

        m_gameOverOverlay.setSize(sf::Vector2f(600, 900));
        m_gameOverOverlay.setFillColor(sf::Color(150, 150, 150, 150));
    }

    void Game::processEvents() {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_songPlayer.stop();
                m_window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

                if (m_sidebar.isPauseClicked(mousePos)) {
                    m_isPaused = !m_isPaused;
                    m_sidebar.togglePause();
                    m_isPaused ? m_songPlayer.pause() : m_songPlayer.resume();
                }

                if (m_sidebar.isRestartClicked(mousePos)) {
                    m_controller.resetGame();
                    m_score = 0;
                    m_sidebar.updateScore(m_score);
                    m_sidebar.showGameOver(false);
                    m_songPlayer.stop();
                    m_songPlayer.loadBackgroundMusic("assets/songs/tetris_classic_song.wav");
                    m_isPaused = false;
                    m_sidebar.togglePause();
                    m_songPlayer.resume();
                }

                if (m_sidebar.isCloseClicked(mousePos)) {
                    m_songPlayer.stop();
                    m_window.close();
                }
            }
        }
    }

    void Game::update(float deltaTime) {
        if (!m_isPaused && !m_controller.isGameOver()) {
            m_controller.handleInput();
            m_controller.update(deltaTime);

            int linesCleared = m_controller.checkAndClearLines();
            if (linesCleared > 0) {
                m_score += linesCleared * 10;
                m_sidebar.updateScore(m_score);
                m_controller.updateFallSpeed(m_score);
            }

            if (m_controller.isGameOver()) {
                m_sidebar.showGameOver(true);
                m_songPlayer.stop();
                m_songPlayer.playGameOverSound("assets/songs/game_over_sound.wav");
            }

            if (auto nextBlock = m_controller.getNextBlock()) {
                m_sidebar.updateNextBlock(std::move(nextBlock));
            }
        }
    }

    void Game::render() {
        m_window.clear();
        m_grid.draw(m_window);
        m_controller.draw(m_window);
        m_sidebar.draw(m_window);

        if (m_isPaused) {
            m_window.draw(m_pauseOverlay);
        }

        if (m_controller.isGameOver()) {
            m_window.draw(m_gameOverOverlay);
        }

        m_window.display();
    }

    void Game::run() {
        while (m_window.isOpen()) {
            processEvents();

            if (!m_isPaused && !m_controller.isGameOver()) {
                float deltaTime = m_deltaClock.restart().asSeconds();
                update(deltaTime);
            }

            render();
        }
    }
}