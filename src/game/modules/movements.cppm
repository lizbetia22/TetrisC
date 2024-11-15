module;

#include <SFML/Graphics.hpp>

export module movements;
import blocks;

export namespace movements {
    class Movements {
    public:
        Movements(blocks::Blocks& blocks, int gridWidth, int gridHeight, int cellSize);
        void handleInput() const;
        void update(float deltaTime);

    private:
        blocks::Blocks& m_blocks;
        int m_gridWidth;
        int m_gridHeight;
        int m_cellSize;

        bool canMove(int dx, int dy) const;
        sf::Clock m_moveClock;
    };
}