#include "../headers/GameGrid.hpp"
#include <iostream>

void GameGrid::gridTick() {
    for (int8_t i = 0; i < cols; i++) {
        for (int8_t j = rows - 2; j >= 0; j--) {
            if (!grid[i][j].isHidden() && grid[i][j + 1].isHidden()) {
                grid[i][j + 1] = grid[i][j];
                grid[i][j].display(false);
            }
        }
    }
}

void GameGrid::blockDestroy(sf::Rect<int> span) {
    for (uint8_t i = span.left; i < span.width + span.left; i++) {
        for (uint8_t j = span.top; j < span.height + span.top; j++) {
            grid[i][j].display(false);
            grid[i][j].fetchLetter().setString("");
        }
    }
}

void GameGrid::blockDispay(sf::Vector2u coord, bool visible) {
    grid[coord.x][coord.y].display(visible);
}

void GameGrid::blockDisplay(sf::Vector2u posInit, sf::Vector2u span, bool visible) {
    for (uint8_t j = posInit.y; j < posInit.y + span.y; j++) {
        for (uint8_t i = posInit.x; i < posInit.x + span.x; i++) {
            grid[i][j].display(visible);
        }
    }
}

void GameGrid::initGrid() {
    gridBorder = sf::RectangleShape(sf::Vector2f(336, 486));
    gridBorder.setPosition(sf::Vector2f(312, 27));
    gridBorder.setOutlineColor(sf::Color(125, 125, 125));
    gridBorder.setOutlineThickness(5);
    gridBorder.setFillColor(sf::Color(0, 0, 0, 0));

    grid = std::vector<std::vector<LetterBlock>>(cols, std::vector<LetterBlock>(rows));

    for(int j=0; j < rows; j++ ){
        for (int i=0; i < cols; i++){
            grid[i][j].setPosition(sf::Vector2f(312+33.6*i, 27+32.4*j));
            grid[i][j].display(false);
        }
    }

        blockDisplay({1,1}, {4,1}, true);

    
}

GameGrid::GameGrid(uint8_t cols, uint8_t rows) : cols(cols), rows(rows) {
    initGrid();
}


void GameGrid::render(sf::RenderTarget *target){

    target->draw(gridBorder);
    for(int j = 0; j < rows; j++ ){
        for (int i = 0; i< cols; i++){
            grid[i][j].render(target);
        }
    }
}

void GameGrid::update() {
    if(tick == 60) {
        gridTick();
        tick = 0;
    }
    tick++;
}