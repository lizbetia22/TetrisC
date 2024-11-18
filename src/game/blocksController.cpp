module;

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

module blocksController;

namespace blocksController {
     BlocksController::BlocksController(const int gridWidth, const int gridHeight, const int cellSize, const sf::Texture& texture)
        : m_gridWidth(gridWidth)
        , m_gridHeight(gridHeight)
        , m_cellSize(cellSize)
        , m_texture(texture)
        , m_moveClock(std::make_unique<sf::Clock>())
        , m_occupiedCells(gridHeight, std::vector<int>(gridWidth, 0))
    {
        createNewBlock();
    }

    void BlocksController::createNewBlock() {
        int shapeType = std::rand() % 7;
        m_activeBlock = std::make_unique<blocks::Blocks>(m_cellSize, m_texture, shapeType);
    }

    bool BlocksController::canMove(const int dx, const int dy) const {
        if (!m_activeBlock) return false;

        for (const auto& block : m_activeBlock->getBlocks()) {
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

    bool BlocksController::canRotate() const {
         if (!m_activeBlock) return false;

         auto currentPositions = m_activeBlock->getPositions();

         sf::Vector2f center = currentPositions[1];

         for (int i = 0; i < 4; ++i) {
             float dx = currentPositions[i].x - center.x;
             float dy = currentPositions[i].y - center.y;

             sf::Vector2f rotatedPos(
                 center.x - dy,
                 center.y + dx
             );

             int gridX = static_cast<int>(rotatedPos.x / m_cellSize);
             int gridY = static_cast<int>(rotatedPos.y / m_cellSize);

             if (gridX < 0 || gridX >= m_gridWidth ||
                 gridY >= m_gridHeight || gridY < 0 ||
                 (gridY >= 0 && m_occupiedCells[gridY][gridX] == 1)) {
                 return false;
                 }
         }

         return true;
     }

    void BlocksController::lockBlock() {
        if (!m_activeBlock) return;

        for (const auto& block : m_activeBlock->getBlocks()) {
            const sf::Vector2f position = block->getPosition();
            int x = static_cast<int>(position.x) / m_cellSize;
            int y = static_cast<int>(position.y) / m_cellSize;

            if (y >= 0 && x >= 0 && x < m_gridWidth && y < m_gridHeight) {
                m_occupiedCells[y][x] = 1;
            }
        }

        m_lockedBlocks.push_back(std::move(m_activeBlock));

        createNewBlock();
    }

    void BlocksController::handleInput() const {
        if (!m_activeBlock) return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (canMove(-1, 0)) {
                m_activeBlock->move(-1, 0);
                sf::sleep(sf::milliseconds(150));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (canMove(1, 0)) {
                m_activeBlock->move(1, 0);
                sf::sleep(sf::milliseconds(150));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (canMove(0, 1)) {
                m_activeBlock->move(0, 1);
                sf::sleep(sf::milliseconds(150));
            }
        }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
             if (canRotate()) {
                 m_activeBlock->rotateShape();
                 sf::sleep(sf::milliseconds(150));
             }
         }
    }

    void BlocksController::update(float deltaTime) {
        if (!m_activeBlock) return;

        if (m_moveClock->getElapsedTime().asSeconds() > 1.0f) {
            if (canMove(0, 1)) {
                m_activeBlock->move(0, 1);
            } else {
                lockBlock();
            }
            m_moveClock->restart();
        }
    }

    void BlocksController::draw(sf::RenderWindow& window) const {
        for (const auto& block : m_lockedBlocks) {
            block->draw(window);
        }
        if (m_activeBlock) {
            m_activeBlock->draw(window);
        }
    }
}