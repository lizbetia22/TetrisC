module;
#include <SFML/Graphics.hpp>
export module Grid;

export class Grid {
public:
    Grid(int windowWidth, int windowHeight, int cellSize);

    void draw(sf::RenderWindow& window);

private:
    int m_windowWidth;
    int m_windowHeight;
    int m_cellSize;
    sf::VertexArray m_gridLines;
};

export Grid::Grid(int windowWidth, int windowHeight, int cellSize)
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

export void Grid::draw(sf::RenderWindow& window)
{
    window.draw(m_gridLines);
}
