module;

#include <SFML/Graphics.hpp>

export module tetris;

import grid;
import blocks;
import sidebar;
import blocksController;
import songController;

export namespace tetris {
    class Game {
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update(float deltaTime);
        void render();

        sf::RenderWindow m_window;
        songController::SongPlayer m_songPlayer;
        grid::Grid m_grid;
        sidebar::Sidebar m_sidebar;
        blocksController::BlocksController m_controller;

        sf::RectangleShape m_pauseOverlay;
        sf::RectangleShape m_gameOverOverlay;
        sf::Texture m_tileTexture;

        sf::Clock m_deltaClock;
        int m_score = 0;
        bool m_isPaused = false;
    };
}