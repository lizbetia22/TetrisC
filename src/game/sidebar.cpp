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
    int buttonWidth = 150;
    int buttonHeight = 60;
    int spacing = 25;
    int sidebarWidth = 300;

    float buttonX = gridWidth * 60 + (sidebarWidth - buttonWidth) / 2;

    m_pauseButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    m_pauseButton.setFillColor(buttonColor);
    m_pauseButton.setPosition(buttonX, 100);

    m_pauseText.setFont(m_font);
    m_pauseText.setString("Pause");
    m_pauseText.setCharacterSize(24);
    m_pauseText.setFillColor(textColor);
    m_pauseText.setPosition(
        buttonX + (buttonWidth - m_pauseText.getLocalBounds().width) / 2,
        100 + (buttonHeight - m_pauseText.getLocalBounds().height) / 2
    );

    m_restartButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    m_restartButton.setFillColor(buttonColor);
    m_restartButton.setPosition(buttonX, 100 + buttonHeight + spacing);

    m_restartText.setFont(m_font);
    m_restartText.setString("Restart");
    m_restartText.setCharacterSize(24);
    m_restartText.setFillColor(textColor);
    m_restartText.setPosition(
        buttonX + (buttonWidth - m_restartText.getLocalBounds().width) / 2,
        100 + buttonHeight + spacing + (buttonHeight - m_restartText.getLocalBounds().height) / 2
    );

    m_closeButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    m_closeButton.setFillColor(buttonColor);
    m_closeButton.setPosition(buttonX, 100 + 2 * (buttonHeight + spacing));

    m_closeText.setFont(m_font);
    m_closeText.setString("Close");
    m_closeText.setCharacterSize(24);
    m_closeText.setFillColor(textColor);
    m_closeText.setPosition(
        buttonX + (buttonWidth - m_closeText.getLocalBounds().width) / 2,
        100 + 2 * (buttonHeight + spacing) + (buttonHeight - m_closeText.getLocalBounds().height) / 2
    );

    m_nextBlockText.setFont(m_font);
    m_nextBlockText.setString("Next Block:");
    m_nextBlockText.setCharacterSize(40);
    m_nextBlockText.setFillColor(sf::Color::White);
    m_nextBlockText.setPosition(gridWidth * 60 + 20, 380);

    m_nextBlockPreview.setSize(sf::Vector2f(220, 220));
    m_nextBlockPreview.setFillColor(sf::Color(0, 0, 0));
    m_nextBlockPreview.setPosition(gridWidth * 60 + 20, 450);

    m_gameOverText.setFont(m_font);
    m_gameOverText.setString("GAME OVER");
    m_gameOverText.setCharacterSize(50);
    m_gameOverText.setFillColor(sf::Color::Red);
    m_gameOverText.setPosition(
        gridWidth * 60 + (300 - m_gameOverText.getLocalBounds().width) / 2,
        800
    );
    m_isGameOver = false;
}
    void Sidebar::draw(sf::RenderWindow& window) const {
        window.draw(m_scoreText);
        window.draw(m_pauseButton);
        window.draw(m_pauseText);
        window.draw(m_restartButton);
        window.draw(m_restartText);
        window.draw(m_closeButton);
        window.draw(m_closeText);
        window.draw(m_nextBlockText);
        window.draw(m_nextBlockPreview);
        if (m_nextBlock) {
            m_nextBlock->draw(window);
        }
       if (m_isGameOver) {
           window.draw(m_gameOverText);
       }
    }

    void Sidebar::updateScore(int newScore) {
        m_score = newScore;
        m_scoreText.setString("Score: " + std::to_string(m_score));
    }

    void Sidebar::showGameOver(bool isGameOver) {
       m_isGameOver = isGameOver;
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

    void Sidebar::updateNextBlock(std::unique_ptr<blocks::Blocks> nextBlock) {
        m_nextBlock = std::move(nextBlock);
        if (m_nextBlock) {
            float previewX = m_nextBlockPreview.getPosition().x + 30;
            float previewY = m_nextBlockPreview.getPosition().y + 30;

            auto positions = m_nextBlock->getPositions();
            float minX = positions[0].x;
            float minY = positions[0].y;

            for (const auto& pos : positions) {
                minX = std::min(minX, pos.x);
                minY = std::min(minY, pos.y);
            }

            float offsetX = previewX - minX;
            float offsetY = previewY - minY;

            auto newPositions = positions;
            for (auto& pos : newPositions) {
                pos.x += offsetX;
                pos.y += offsetY;
            }

            m_nextBlock->setPositions(newPositions);
        }
    }
}