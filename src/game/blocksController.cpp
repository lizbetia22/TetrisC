module;

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <iostream>


module blocksController;

namespace blocksController {
    BlocksController::BlocksController(
   const int gridWidth,
   const int gridHeight,
   const int cellSize,
   const sf::Texture& texture,
   songController::SongPlayer& songPlayer)
   : m_gridWidth(gridWidth)
   , m_gridHeight(gridHeight)
   , m_cellSize(cellSize)
   , m_texture(texture)
   , m_songPlayer(songPlayer)
   , m_moveClock(std::make_unique<sf::Clock>())
   , m_occupiedCells(gridHeight, std::vector<int>(gridWidth, 0))
    {
        createNewBlock();
        m_nextBlock = std::make_unique<blocks::Blocks>(m_cellSize, m_texture, std::rand() % 7);
    }

    void BlocksController::createNewBlock() {
        if (m_nextBlock) {
            m_activeBlock = std::move(m_nextBlock);
        } else {
            int shapeType = std::rand() % 7;
            m_activeBlock = std::make_unique<blocks::Blocks>(m_cellSize, m_texture, shapeType);
        }

        int nextShapeType = std::rand() % 7;
        m_nextBlock = std::make_unique<blocks::Blocks>(m_cellSize, m_texture, nextShapeType);
    }

    std::unique_ptr<blocks::Blocks> BlocksController::getNextBlock() const {
        if (!m_nextBlock) return nullptr;
        return m_nextBlock->clone();
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

        m_songPlayer.playCollisionSound("assets/songs/click_sound.wav");
        m_songPlayer.setCollisionSoundVolume(100.0f);

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

    int BlocksController::checkAndClearLines() {
    std::vector<int> linesToClear;

    for (int y = m_gridHeight - 1; y >= 0; --y) {
        bool lineIsFull = true;
        for (int x = 0; x < m_gridWidth; ++x) {
            if (m_occupiedCells[y][x] == 0) {
                lineIsFull = false;
                break;
            }
        }
        if (lineIsFull) {
            linesToClear.push_back(y);
        }
    }
    if (linesToClear.empty()) return 0;
    auto it = m_lockedBlocks.begin();
    while (it != m_lockedBlocks.end()) {
        auto positions = (*it)->getPositions();
        bool hasBlocksInClearedLines = false;
        bool shouldRemoveBlock = true;

        for (const auto& pos : positions) {
            int blockY = static_cast<int>(pos.y / m_cellSize);
            if (std::find(linesToClear.begin(), linesToClear.end(), blockY) != linesToClear.end()) {
                hasBlocksInClearedLines = true;
            } else {
                shouldRemoveBlock = false;
            }
        }
        if (hasBlocksInClearedLines) {
            if (shouldRemoveBlock) {
                it = m_lockedBlocks.erase(it);
                continue;
            } else {
                std::vector<sf::Vector2f> remainingPositions;
                auto currentPositions = (*it)->getPositions();

                for (const auto& pos : currentPositions) {
                    int blockY = static_cast<int>(pos.y / m_cellSize);
                    if (std::find(linesToClear.begin(), linesToClear.end(), blockY) == linesToClear.end()) {
                        remainingPositions.push_back(pos);
                    }
                }

                if (!remainingPositions.empty()) {
                    std::array<sf::Vector2f, 4> newPositions;
                    for (size_t i = 0; i < 4; ++i) {
                        newPositions[i] = i < remainingPositions.size() ? remainingPositions[i] : remainingPositions.back();
                    }
                    (*it)->setPositions(newPositions);
                }
            }
        }
        ++it;
    }
    int dropDistance = 0;
    for (auto& block : m_lockedBlocks) {
        auto positions = block->getPositions();
        bool shouldMove = false;
        int minDropDistance = m_gridHeight;

        for (const auto& pos : positions) {
            int blockY = static_cast<int>(pos.y / m_cellSize);
            dropDistance = 0;

            for (int clearedY : linesToClear) {
                if (blockY < clearedY) {
                    dropDistance++;
                }
            }

            if (dropDistance > 0) {
                shouldMove = true;
                minDropDistance = std::min(minDropDistance, dropDistance);
            }
        }

        if (shouldMove) {
            std::array<sf::Vector2f, 4> newPositions;
            for (size_t i = 0; i < positions.size(); ++i) {
                newPositions[i] = positions[i];
                newPositions[i].y += minDropDistance * m_cellSize;
            }
            block->setPositions(newPositions);
        }
    }

    for (int clearedY : linesToClear) {
        for (int y = clearedY; y > 0; --y) {
            for (int x = 0; x < m_gridWidth; ++x) {
                m_occupiedCells[y][x] = m_occupiedCells[y - 1][x];
            }
        }
        for (int x = 0; x < m_gridWidth; ++x) {
            m_occupiedCells[0][x] = 0;
        }
    }

    for (size_t i = 0; i < linesToClear.size(); ++i) {
        m_songPlayer.playCollisionSound("assets/songs/pop_sound.wav");
    }
        return linesToClear.size();
}

    void BlocksController::resetGame() {
        m_lockedBlocks.clear();
        m_occupiedCells = std::vector<std::vector<int>>(m_gridHeight, std::vector<int>(m_gridWidth, 0));
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
              //  checkAndClearLines();
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