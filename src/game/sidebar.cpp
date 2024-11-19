module;

#include <SFML/Graphics.hpp>
#include <string>

module sidebar;

namespace sidebar {
    Sidebar::Sidebar(int windowWidth, int windowHeight, int gridWidth) : m_score(0) {
        if (!m_font.loadFromFile("assets/fonts/ASMAN.ttf")) {
            throw std::runtime_error("Could not load font");
        }

        m_scoreText.setFont(m_font);
        m_scoreText.setCharacterSize(40);
        m_scoreText.setFillColor(sf::Color::White);
        m_scoreText.setPosition(gridWidth * 60 + 20, 20);
        m_scoreText.setString("Score: 0");

        sf::Color buttonColor(100, 100, 100);
        sf::Color textColor(255, 255, 255);
        int buttonWidth = 100;
        int buttonHeight = 50;
        int spacing = 20;

        m_pauseButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        m_pauseButton.setFillColor(buttonColor);
        m_pauseButton.setPosition(gridWidth * 60 + 20, 100);

        m_pauseText.setFont(m_font);
        m_pauseText.setString("Pause");
        m_pauseText.setCharacterSize(20);
        m_pauseText.setFillColor(textColor);
        m_pauseText.setPosition(m_pauseButton.getPosition().x + 20, m_pauseButton.getPosition().y + 10);

        m_restartButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        m_restartButton.setFillColor(buttonColor);
        m_restartButton.setPosition(gridWidth * 60 + 20, 100 + buttonHeight + spacing);

        m_restartText.setFont(m_font);
        m_restartText.setString("Restart");
        m_restartText.setCharacterSize(20);
        m_restartText.setFillColor(textColor);
        m_restartText.setPosition(m_restartButton.getPosition().x + 20, m_restartButton.getPosition().y + 10);

        m_closeButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        m_closeButton.setFillColor(buttonColor);
        m_closeButton.setPosition(gridWidth * 60 + 20, 100 + 2 * (buttonHeight + spacing));

        m_closeText.setFont(m_font);
        m_closeText.setString("Close");
        m_closeText.setCharacterSize(20);
        m_closeText.setFillColor(textColor);
        m_closeText.setPosition(m_closeButton.getPosition().x + 20, m_closeButton.getPosition().y + 10);
    }

    void Sidebar::draw(sf::RenderWindow& window) {
        window.draw(m_scoreText);
        window.draw(m_pauseButton);
        window.draw(m_pauseText);
        window.draw(m_restartButton);
        window.draw(m_restartText);
        window.draw(m_closeButton);
        window.draw(m_closeText);
    }

    void Sidebar::updateScore(int newScore) {
        m_score = newScore;
        m_scoreText.setString("Score: " + std::to_string(m_score));
    }

    bool Sidebar::isPauseClicked(const sf::Vector2f& mousePos) const {
        return m_pauseButton.getGlobalBounds().contains(mousePos);
    }

    bool Sidebar::isRestartClicked(const sf::Vector2f& mousePos) const {
        return m_restartButton.getGlobalBounds().contains(mousePos);
    }

    bool Sidebar::isCloseClicked(const sf::Vector2f& mousePos) const {
        return m_closeButton.getGlobalBounds().contains(mousePos);
    }
}