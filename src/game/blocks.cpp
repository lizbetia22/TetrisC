module;

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <vector>
#include <utility>

module blocks;

namespace blocks {

    const std::vector<std::array<std::pair<int, int>, 4>> shapes = {
        {{ {0, 0}, {1, 0}, {2, 0}, {3, 0} }}, // Forme I
        {{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }}, // Forme O
        {{ {0, 0}, {1, 0}, {2, 0}, {2, 1} }}, // Forme L
        {{ {0, 0}, {1, 0}, {2, 0}, {2, -1} }}, // Forme J
        {{ {0, 0}, {1, 0}, {2, 0}, {1, 1} }}, // Forme T
        {{ {0, 0}, {0, 1}, {1, 1}, {1, 2} }}, // Forme S
        {{ {1, 0}, {2, 0}, {0, 1}, {1, 1} }}  // Forme Z
    };

    Blocks::Blocks(const int cellSize, const sf::Texture& texture, const int tileIndex)
         : m_cellSize(cellSize), m_blocks{}
    {
        initializeBlocks(texture, tileIndex);
    }

    void Blocks::initializeBlocks(const sf::Texture& texture, int shapeType) {
        m_shape = shapes[shapeType];

        const int tileSize = 512;
        const int tileX = shapeType * tileSize;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i] = std::make_unique<sf::Sprite>();
            m_blocks[i]->setTexture(texture);
            m_blocks[i]->setTextureRect(sf::IntRect(tileX, 0, tileSize, tileSize));
            m_blocks[i]->setPosition(m_shape[i].first * m_cellSize, m_shape[i].second * m_cellSize);
            m_blocks[i]->setScale(
                static_cast<float>(m_cellSize) / static_cast<float>(tileSize),
                static_cast<float>(m_cellSize) / static_cast<float>(tileSize)
            );
        }
    }

    void Blocks::draw(sf::RenderWindow& window) const {
        for (const auto& block : m_blocks) {
            window.draw(*block);
        }
    }

    void Blocks::move(const int dx, const int dy) const {
        for (auto& block : m_blocks) {
            block->move(dx * m_cellSize, dy * m_cellSize);
        }
    }

    void Blocks::rotateShape() const {
        auto currentPositions = getPositions();

        sf::Vector2f center = currentPositions[1];

        std::array<sf::Vector2f, 4> newPositions;
        for (int i = 0; i < 4; ++i) {
            float dx = currentPositions[i].x - center.x;
            float dy = currentPositions[i].y - center.y;

            newPositions[i].x = center.x - dy;
            newPositions[i].y = center.y + dx;
        }

        setPositions(newPositions);
    }

    std::array<sf::Vector2f, 4> Blocks::getPositions() const {
        std::array<sf::Vector2f, 4> positions;
        for (int i = 0; i < 4; ++i) {
            positions[i] = m_blocks[i]->getPosition();
        }
        return positions;
    }

    void Blocks::setPositions(const std::array<sf::Vector2f, 4>& newPositions) const {
        for (int i = 0; i < 4; ++i) {
            m_blocks[i]->setPosition(newPositions[i]);
        }
    }

    const std::array<std::unique_ptr<sf::Sprite>, 4>& Blocks::getBlocks() const {
        return m_blocks;
    }
}
