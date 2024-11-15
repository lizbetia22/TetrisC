module;

#include <SFML/Graphics.hpp>
#include <memory>

export module movements;
import blocks;

export namespace movements {
    class Movements {
    public:
        Movements(blocks::Blocks& blocks, int gridWidth, int gridHeight, int cellSize);
        ~Movements() = default;

        Movements(const Movements&) = delete;
        Movements& operator=(const Movements&) = delete;

        void handleInput() const;
        void update(float deltaTime) const;

    private:
        blocks::Blocks& m_blocks;
        int m_gridWidth;
        int m_gridHeight;
        int m_cellSize;

        bool canMove(int dx, int dy) const;
        std::unique_ptr<sf::Clock> m_moveClock;
    };
}