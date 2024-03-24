#include "../headers/GameGrid.hpp"

void GameGrid::gridTick() {
    for (uint8_t i = 0; i < cols; i++) {
        for (uint8_t j = rows - 2; j != 0; j--) {
            if (!grid[i][j].isHidden() && grid[i][j + 1].isHidden()) {
                grid[i][j + 1] = grid[i][j];
            }
        }
    }
}

void GameGrid::blockDestroy(sf::Rect<int> span) {
    for (uint8_t i = span.left; i < span.width + span.left; i++) {
        for (uint8_t j = span.top; j < span.height + span.top; j++) {
            grid[i][j].display(false);
            grid[i][j].fetchLetter() = ' ';
        }
    }
}

void GameGrid::blockDispay(sf::Vector2u coord, bool visible) {
    grid[coord.x][coord.y].display(true);
}

void GameGrid::blockDisplay(sf::Rect<uint8_t> span, bool visible) {
    for (uint8_t i = span.left; i < span.width + span.left; i++) {
        for (uint8_t j = span.top; j < span.height + span.top; j++) {
            grid[i][j].display(true);
        }
    }
}

void GameGrid::initGrid() {
    gridBorder = sf::RectangleShape(sf::Vector2f(336,486));
    gridBorder.setPosition(sf::Vector2f(312,27));
    gridBorder.setOutlineColor(sf::Color(125,125,125));
    gridBorder.setOutlineThickness(3);
    gridBorder.setFillColor(sf::Color(0,0,0,0));
    
}

GameGrid::GameGrid(uint8_t cols, uint8_t rows) : cols(cols), rows(rows) {
    initGrid();
}

