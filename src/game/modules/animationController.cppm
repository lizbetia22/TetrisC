module;
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <functional>

export module animation;

export namespace animation {
    class AnimationController {
    public:
        AnimationController(int gridWidth, int cellSize, const sf::Texture& texture);

        void startLineAnimation(const std::vector<int>& linesToClear);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window) const;
        [[nodiscard]] bool isAnimationComplete() const;

        void operator()(const std::vector<int>& linesToClear);
        bool operator==(const AnimationController& other) const;

    private:
        struct AnimationLine {
            std::vector<std::unique_ptr<sf::Sprite>> sprites;
            float opacity;
            float animationTimer;
        };

        std::vector<AnimationLine> m_animationLines;
        int m_gridWidth;
        int m_cellSize;
        const sf::Texture& m_texture;
        bool m_animationActive;
    };
}
