#include <SFML/Graphics.hpp>

import tetris;

int main() {
    try {
        tetris::Game game;
        game.run();
    } catch (const std::exception& e) {
        return -1;
    }
    return 0;
}