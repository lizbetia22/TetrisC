module;

#include <SFML/Graphics.hpp>

export module sidebar;

export namespace sidebar {
    class Sidebar {
    public:
        Sidebar(int windowWidth, int windowHeight, int gridWidth);
        void draw(sf::RenderWindow& window);
        void updateScore(int newScore);
        bool isPauseClicked(const sf::Vector2f& mousePos) const;
        bool isRestartClicked(const sf::Vector2f& mousePos) const;
        bool isCloseClicked(const sf::Vector2f& mousePos) const;

    private:
        sf::Font m_font;
        sf::Text m_scoreText;
        sf::RectangleShape m_pauseButton;
        sf::RectangleShape m_restartButton;
        sf::RectangleShape m_closeButton;
        sf::Text m_pauseText;
        sf::Text m_restartText;
        sf::Text m_closeText;
        int m_score;
    };
}