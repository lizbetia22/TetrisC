module;

#include <SFML/Graphics.hpp>
#include <array>

export module blocks;

export namespace blocks {
    class Blocks {
    public:
        Blocks(int cellSize, const sf::Texture& texture, int tileIndex);

        void draw(sf::RenderWindow& window) const;
        void move(int dx, int dy);
        const std::array<sf::Sprite, 4>& getBlocks() const;

    private:
        int m_cellSize;
        std::array<sf::Sprite, 4> m_blocks;

        void initializeBlocks(const sf::Texture& texture, int tileIndex);
    };
}