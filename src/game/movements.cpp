module;

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

module movements;

namespace movements {
    Movements::Movements(blocks::Blocks& blocks, const int gridWidth, const int gridHeight, const int cellSize)
        : m_blocks(blocks),
          m_gridWidth(gridWidth),
          m_gridHeight(gridHeight),
          m_cellSize(cellSize),
          m_moveClock(std::make_unique<sf::Clock>())
    {}

    bool Movements::canMove(const int dx, const int dy) const {
        for (const auto& block : m_blocks.getBlocks()) {
            sf::Vector2f futurePosition = block->getPosition() + sf::Vector2f(dx * m_cellSize, dy * m_cellSize);

            if (futurePosition.x < 0 || futurePosition.x >= m_gridWidth * m_cellSize ||
                futurePosition.y >= m_gridHeight * m_cellSize) {
                return false;
                }
        }
        return true;
    }


    void Movements::handleInput() const {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (canMove(-1, 0)) {
                m_blocks.move(-1, 0);
                sf::sleep(sf::milliseconds(150));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (canMove(1, 0)) {
                m_blocks.move(1, 0);
                sf::sleep(sf::milliseconds(150));
            }
        }
    }

    void Movements::update(float deltaTime) const {
        if (m_moveClock->getElapsedTime().asSeconds() > 1.0f) {
            if (canMove(0, 1)) {
                m_blocks.move(0, 1);
            }
            m_moveClock->restart();
        }
    }
}
