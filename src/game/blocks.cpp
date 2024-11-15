module;

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

module blocks;

namespace blocks {
    Blocks::Blocks(const int cellSize, const sf::Texture& texture, const int tileIndex)
         : m_cellSize(cellSize), m_blocks{}
    {
        initializeBlocks(texture, tileIndex);
    }

    void Blocks::initializeBlocks(const sf::Texture& texture, const int tileIndex) {
        int tileSize = 512;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i] = std::make_unique<sf::Sprite>();
            m_blocks[i]->setTexture(texture);
            m_blocks[i]->setTextureRect(sf::IntRect(tileIndex * tileSize, 0, tileSize, tileSize));
            m_blocks[i]->setPosition((3 + i) * m_cellSize, 0);
            m_blocks[i]->setScale(
                static_cast<float>(m_cellSize) / tileSize,
                static_cast<float>(m_cellSize) / tileSize
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

    const std::array<std::unique_ptr<sf::Sprite>, 4>& Blocks::getBlocks() const {
        return m_blocks;
    }
}
