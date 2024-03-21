#include "../lib/GameGrid.hpp"

void GameGrid::gridTick() {
    for (uint8_t i = 0; i < cols; i++) {
        for (uint8_t j = rows - 2; j != 0; j--) {
            if (!grid[i][j].isHidden() && grid[i][j + 1].isHidden()) {
                grid[i][j + 1] = grid[i][j];
            }
        }
    }
}

void GameGrid::gridDestroy(sf::Rect<int> span) {
    for (uint8_t i = span.left; i < span.width + span.left; i++) {
        for (uint8_t j = span.top; j < span.height + span.top; j++) {
            grid[i][j].display(false);
            grid[i][j].fetchLetter() = ' ';
        }
    }
}

void GameGrid::gridDispay(sf::Vector2u coord, bool visible) {
    grid[coord.x][coord.y].display(true);
}

void GameGrid::gridDisplay(sf::Rect<uint8_t> span, bool visible) {
    for (uint8_t i = span.left; i < span.width + span.left; i++) {
        for (uint8_t j = span.top; j < span.height + span.top; j++) {
            grid[i][j].display(true);
        }
    }
}
