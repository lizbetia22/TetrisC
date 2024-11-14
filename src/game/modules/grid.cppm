module;

#include <SFML/Graphics.hpp>

export module grid;

export namespace grid {
    class Grid {
    public:
        Grid(int windowWidth, int windowHeight, int cellSize);

        void draw(sf::RenderWindow& window) const;

    private:
        int m_windowWidth;
        int m_windowHeight;
        int m_cellSize;
        sf::VertexArray m_gridLines;
    };
}
