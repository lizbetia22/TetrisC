module;

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

export module blocksController;
import blocks;

export namespace blocksController {
    class BlocksController {
    public:
        BlocksController(blocks::Blocks& blocks, int gridWidth, int gridHeight, int cellSize);
        ~BlocksController() = default;

        void handleInput() const;
        void update(float deltaTime);
        bool canMove(int dx, int dy) const;
        void lockBlock();

    private:
        blocks::Blocks& m_blocks;
        int m_gridWidth;
        int m_gridHeight;
        int m_cellSize;
        std::unique_ptr<sf::Clock> m_moveClock;
        std::vector<std::vector<int>> m_occupiedCells;
    };
}