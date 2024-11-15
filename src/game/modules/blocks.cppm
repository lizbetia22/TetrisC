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

        [[nodiscard]] const std::array<std::unique_ptr<sf::Sprite>, 4>& getBlocks() const;

    private:
        int m_cellSize;
        std::array<std::unique_ptr<sf::Sprite>, 4> m_blocks;

        void initializeBlocks(const sf::Texture& texture, int tileIndex);
    };
}