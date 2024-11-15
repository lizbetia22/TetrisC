module;

#include <SFML/Graphics.hpp>

export module grid;

export namespace grid {
    class Grid {
    public:
        Grid(int windowWidth, int windowHeight, int cellSize);
        ~Grid() = default;

        Grid(const Grid&) = delete;
        Grid& operator=(const Grid&) = delete;

        void draw(sf::RenderWindow& window) const;

    private:
        int m_windowWidth;
        int m_windowHeight;
        int m_cellSize;
        std::unique_ptr<sf::VertexArray> m_gridLines;
    };
}
