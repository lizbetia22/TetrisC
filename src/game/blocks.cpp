module;

#include <SFML/Graphics.hpp>
#include <array>

module blocks;

namespace blocks {
    Blocks::Blocks(int cellSize, const sf::Texture &texture, int tileIndex): m_cellSize(cellSize) {
        initializeBlocks(texture, tileIndex);
    }

    void Blocks::initializeBlocks(const sf::Texture& texture, int tileIndex) {
        int tileSize = 512;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setTexture(texture);

            m_blocks[i].setTextureRect(sf::IntRect(tileIndex * tileSize, 0, tileSize, tileSize));

            m_blocks[i].setPosition(i * m_cellSize, 0);

            m_blocks[i].setScale(
                static_cast<float>(m_cellSize) / tileSize,
                static_cast<float>(m_cellSize) / tileSize
            );
        }
    }

    void Blocks::draw(sf::RenderWindow& window) const {
        for (const auto& block : m_blocks) {
            window.draw(block);
        }
    }
}
