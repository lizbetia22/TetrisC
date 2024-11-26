module;

#include <SFML/Graphics.hpp>
#include <functional>

export module sidebar;
import blocks;

export namespace sidebar {
    class Sidebar {
    public:
        Sidebar(int windowWidth, int windowHeight, int gridWidth);

        void draw(sf::RenderWindow& window) const;
        void updateScore(int newScore);
        bool isPauseClicked(const sf::Vector2f& mousePos) const;
        bool isRestartClicked(const sf::Vector2f& mousePos) const;
        bool isCloseClicked(const sf::Vector2f& mousePos) const;
        void updateNextBlock(std::unique_ptr<blocks::Blocks> nextBlock);
        void showGameOver(bool isGameOver);

        void operator()(int newScore);
        void operator()(std::unique_ptr<blocks::Blocks> nextBlock);
        bool operator==(const Sidebar& other) const;

    private:
        sf::Font m_font;
        sf::Text m_scoreText;
        sf::Text m_nextBlockText;
        sf::RectangleShape m_pauseButton;
        sf::RectangleShape m_restartButton;
        sf::RectangleShape m_closeButton;
        sf::Text m_pauseText;
        sf::Text m_restartText;
        sf::Text m_closeText;
        sf::RectangleShape m_nextBlockPreview;
        std::unique_ptr<blocks::Blocks> m_nextBlock;
        int m_score;
        sf::Text m_gameOverText;
        bool m_isGameOver;
    };
}