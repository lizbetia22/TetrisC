module;

#include <SFML/Graphics.hpp>

module grid;

namespace grid {
    Grid::Grid(const int windowWidth, const int windowHeight, const int cellSize)
        : m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_cellSize(cellSize),
          m_gridLines(sf::Lines)
    {
        const int gridWidth = windowWidth / cellSize;
        const int gridHeight = windowHeight / cellSize;

        for (int i = 0; i <= gridHeight; ++i)
        {
            m_gridLines.append(sf::Vertex(sf::Vector2f(0.f, i * cellSize), sf::Color::White));
            m_gridLines.append(sf::Vertex(sf::Vector2f(windowWidth, i * cellSize), sf::Color::White));
        }

        for (int i = 0; i <= gridWidth; ++i)
        {
            m_gridLines.append(sf::Vertex(sf::Vector2f(i * cellSize, 0.f), sf::Color::White));
            m_gridLines.append(sf::Vertex(sf::Vector2f(i * cellSize, windowHeight), sf::Color::White));
        }
    }

    void Grid::draw(sf::RenderWindow& window) const {
        window.draw(m_gridLines);
    }
}
