module;

#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <ranges>

module sidebar;

namespace sidebar {
    Sidebar::Sidebar(int windowWidth, int windowHeight, int gridWidth) :
        m_score(0),
        m_isGameOver(false),
        m_isPaused(false) {

        auto loadFont = [this]() {
            if (!m_font.loadFromFile("assets/fonts/stocky.ttf")) {
                throw std::runtime_error("Could not load font");
            }
        };

        auto configureText = [this](sf::Text& text, const std::string& str,
                                          unsigned int size, sf::Color color,
                                          sf::Vector2f position) {
            text.setFont(m_font);
            text.setString(str);
            text.setCharacterSize(size);
            text.setFillColor(color);
            text.setPosition(position);
        };

        auto configureButton = [this](sf::RectangleShape& button, sf::Text& buttonText,
                                            const std::string& text, sf::Vector2f position) {
            sf::Color buttonColor(100, 100, 100);
            sf::Color textColor(255, 255, 255);
            int buttonWidth = 150;
            int buttonHeight = 60;

            button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
            button.setFillColor(buttonColor);
            button.setPosition(position);

            buttonText.setFont(m_font);
            buttonText.setString(text);
            buttonText.setCharacterSize(24);
            buttonText.setFillColor(textColor);
            buttonText.setPosition(
                position.x + (buttonWidth - buttonText.getLocalBounds().width) / 2,
                position.y + (buttonHeight - buttonText.getLocalBounds().height) / 2
            );
        };

        loadFont();

        configureText(m_scoreText, "Score: 0", 40, sf::Color::White,
                            sf::Vector2f(gridWidth * 60 + 20, 20));

        int sidebarWidth = 300;
        int buttonWidth = 150;
        int buttonHeight = 60;
        int spacing = 25;

        float buttonX = gridWidth * 60 + (sidebarWidth - buttonWidth) / 2;

        configureButton(m_pauseButton, m_pauseText, "Pause",
                              sf::Vector2f(buttonX, 100));

        configureButton(m_restartButton, m_restartText, "Restart",
                              sf::Vector2f(buttonX, 100 + buttonHeight + spacing));

        configureButton(m_closeButton, m_closeText, "Close",
                              sf::Vector2f(buttonX, 100 + 2 * (buttonHeight + spacing)));

        configureText(m_nextBlockText, "Next Block:", 40, sf::Color::White,
                            sf::Vector2f(gridWidth * 60 + 20, 380));

        m_nextBlockPreview.setSize(sf::Vector2f(220, 220));
        m_nextBlockPreview.setFillColor(sf::Color(0, 0, 0));
        m_nextBlockPreview.setPosition(gridWidth * 60 + 20, 450);

        configureText(m_gameOverText, "GAME OVER", 40, sf::Color::Red,
                            sf::Vector2f(
                                gridWidth * 60 + (20 - m_gameOverText.getLocalBounds().width) / 2,
                                800
                            ));
    }

    void Sidebar:: togglePause() {
        m_isPaused = !m_isPaused;
        m_pauseText.setString(m_isPaused ? "Continuer" : "Pause");
        float buttonWidth = m_pauseButton.getSize().x;
        float buttonHeight = m_pauseButton.getSize().y;
        m_pauseText.setPosition(
            m_pauseButton.getPosition().x + (buttonWidth - m_pauseText.getLocalBounds().width) / 2,
            m_pauseButton.getPosition().y + (buttonHeight - m_pauseText.getLocalBounds().height) / 2
        );
    }

    void Sidebar::operator()(int newScore) {
        updateScore(newScore);
    }

    void Sidebar::operator()(std::unique_ptr<blocks::Blocks> nextBlock) {
        updateNextBlock(std::move(nextBlock));
    }

    bool Sidebar::operator==(const Sidebar& other) const {
        return m_score == other.m_score &&
               m_isGameOver == other.m_isGameOver;
    }

    void Sidebar::draw(sf::RenderWindow& window) const {
        auto drawElement = [&window](const auto& element) {
            window.draw(element);
        };

        std::vector<std::reference_wrapper<const sf::Drawable>> elements = {
            m_scoreText, m_pauseButton, m_pauseText,
            m_restartButton, m_restartText,
            m_closeButton, m_closeText,
            m_nextBlockText, m_nextBlockPreview
        };

        std::ranges::for_each(elements, drawElement);

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
        auto adjustBlockPosition = [this](const std::unique_ptr<blocks::Blocks>& block) {
            if (block) {
                float previewX = m_nextBlockPreview.getPosition().x + 30;
                float previewY = m_nextBlockPreview.getPosition().y + 30;

                auto positions = block->getPositions();

                float minX = std::ranges::min_element(positions,
                [](const auto& a, const auto& b) {
                     return a.x < b.x;
                     })->x;

                float minY = std::ranges::min_element(positions,
                    [](const auto& a, const auto& b) {
                        return a.y < b.y;
                    })->y;

                float offsetX = previewX - minX;
                float offsetY = previewY - minY;

                for (auto& pos : positions) {
                    pos.x += offsetX;
                    pos.y += offsetY;
                }

                block->setPositions(positions);
            }
        };
        m_nextBlock = std::move(nextBlock);
        adjustBlockPosition(m_nextBlock);
    }
}