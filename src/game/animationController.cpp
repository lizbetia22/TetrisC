module;

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <utility>

module animation;

namespace animation {
    AnimationController::AnimationController(int gridWidth, int cellSize, const sf::Texture& texture)
        : m_gridWidth(gridWidth), m_cellSize(cellSize), m_texture(texture), m_animationActive(false) {}

    void AnimationController::startLineAnimation(const std::vector<int>& linesToClear) {
        if (linesToClear.empty()) return;

        m_animationLines.clear();
        m_animationActive = true;

        for (int lineY : linesToClear) {
            AnimationLine animLine;
            animLine.opacity = 1.0f;
            animLine.animationTimer = 0.0f;

            for (int x = 0; x < m_gridWidth; ++x) {
                auto sprite = std::make_unique<sf::Sprite>();
                sprite->setTexture(m_texture);
                sprite->setTextureRect(sf::IntRect(0, 0, 512, 512));
                sprite->setPosition(x * m_cellSize, lineY * m_cellSize);
                sprite->setScale(
                    static_cast<float>(m_cellSize) / 512.0f,
                    static_cast<float>(m_cellSize) / 512.0f
                );
                animLine.sprites.push_back(std::move(sprite));
            }

            m_animationLines.push_back(std::move(animLine));
        }
    }

    void AnimationController::update(float deltaTime) {
        if (!m_animationActive) return;

        bool allLinesComplete = true;
        for (auto& animLine : m_animationLines) {
            animLine.animationTimer += deltaTime;

            float progress = std::min(animLine.animationTimer / 0.5f, 1.0f);
            animLine.opacity = 1.0f - progress;

            for (auto& sprite : animLine.sprites) {
                sf::Color color = sprite->getColor();
                color.a = static_cast<sf::Uint8>(255 * animLine.opacity);
                sprite->setColor(color);
                sprite->setScale(
                    static_cast<float>(m_cellSize) / 512.0f * (1.0f - progress * 0.5f),
                    static_cast<float>(m_cellSize) / 512.0f * (1.0f - progress * 0.5f)
                );
            }

            if (progress < 1.0f) {
                allLinesComplete = false;
            }
        }

        if (allLinesComplete) {
            m_animationActive = false;
            m_animationLines.clear();
        }
    }

    void AnimationController::draw(sf::RenderWindow& window) const {
        for (const auto& animLine : m_animationLines) {
            for (const auto& sprite : animLine.sprites) {
                window.draw(*sprite);
            }
        }
    }

    bool AnimationController::isAnimationComplete() const {
        return !m_animationActive;
    }
}