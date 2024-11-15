module;

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

module blocksController;

namespace blocksController {
    BlocksController::BlocksController(blocks::Blocks& blocks, const int gridWidth, const int gridHeight, const int cellSize)
     : m_blocks(blocks),
       m_gridWidth(gridWidth),
       m_gridHeight(gridHeight),
       m_cellSize(cellSize),
       m_moveClock(std::make_unique<sf::Clock>()),
       m_occupiedCells(gridHeight, std::vector<int>(gridWidth, 0))

 {}

    bool BlocksController::canMove(const int dx, const int dy) const {
        for (const auto& block : m_blocks.getBlocks()) {
            sf::Vector2f futurePosition = block->getPosition() + sf::Vector2f(dx * m_cellSize, dy * m_cellSize);

            int futureX = static_cast<int>(futurePosition.x) / m_cellSize;
            int futureY = static_cast<int>(futurePosition.y) / m_cellSize;

            if (futureX < 0 || futureX >= m_gridWidth || futureY >= m_gridHeight)
                return false;

            if (futureY >= 0 && m_occupiedCells[futureY][futureX])
                return false;
        }
        return true;
    }

    void BlocksController::lockBlock() {
        for (const auto& block : m_blocks.getBlocks()) {
            const sf::Vector2f position = block->getPosition();

            int x = static_cast<int>(position.x) / m_cellSize;
            int y = static_cast<int>(position.y) / m_cellSize;

            if (y >= 0 && x >= 0 && x < m_gridWidth && y < m_gridHeight) {
                m_occupiedCells[y][x] = 1;
            }
        }

        // TODO : Réinitialiser les blocs pour un nouveau
    }


    void BlocksController::handleInput() const {
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (canMove(0, 1)) {
                m_blocks.move(0, 1);
                sf::sleep(sf::milliseconds(150));
            }
        }
    }

    void BlocksController::update(float deltaTime) {
        if (m_moveClock->getElapsedTime().asSeconds() > 1.0f) {
            if (canMove(0, 1)) {
                m_blocks.move(0, 1);
            }else {
                lockBlock();
            }
            m_moveClock->restart();
        }
    }

}
