module;

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

export module blocksController;
import blocks;

export namespace blocksController {
    class BlocksController {
    public:
        BlocksController(int gridWidth, int gridHeight, int cellSize, const sf::Texture& texture);
        ~BlocksController() = default;

        void handleInput() const;
        void update(float deltaTime);
        void draw(sf::RenderWindow& window) const;

    private:
        bool canMove(int dx, int dy) const;
        void lockBlock();
        void createNewBlock();
        std::unique_ptr<blocks::Blocks> m_activeBlock;
        std::vector<std::unique_ptr<blocks::Blocks>> m_lockedBlocks;
        const sf::Texture& m_texture;
        int m_gridWidth;
        int m_gridHeight;
        int m_cellSize;
        std::unique_ptr<sf::Clock> m_moveClock;
        std::vector<std::vector<int>> m_occupiedCells;
    };
}