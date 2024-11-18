module;

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

export module blocks;

export namespace blocks {
    class Blocks {
    public:
        Blocks(int cellSize, const sf::Texture& texture, int tileIndex);
        ~Blocks() = default;

        Blocks(const Blocks&) = delete;
        Blocks& operator=(const Blocks&) = delete;

        void draw(sf::RenderWindow& window) const;
        void move(int dx, int dy) const;
        void rotateShape() const;

        [[nodiscard]] const std::array<std::unique_ptr<sf::Sprite>, 4>& getBlocks() const;
        [[nodiscard]] std::array<sf::Vector2f, 4> getPositions() const;
        void setPositions(const std::array<sf::Vector2f, 4>& newPositions) const;

    private:
        int m_cellSize;
        std::array<std::unique_ptr<sf::Sprite>, 4> m_blocks;
        void initializeBlocks(const sf::Texture& texture, int tileIndex);
        std::array<std::pair<int, int>, 4> m_shape;
    };
}