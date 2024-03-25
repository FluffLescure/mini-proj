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
            grid[i][j].fetchLetter().setString(" ");
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


    for(int j=0; j < rows; j++ ){
        for (int i=0; i< cols; i++){
            grid[i][j].setPosition(sf::Vector2f(312+33.6*i, 27+32.4*j));
        }
    }


    blockDisplay(sf::Vector2u(3,5), sf::Vector2u(4,4), false);
    
}

GameGrid::GameGrid(uint8_t cols, uint8_t rows) : cols(cols), rows(rows) {
    initGrid();
    
}


void GameGrid::render(sf::RenderTarget *target){
    target->draw(gridBorder);
    target->draw(grid[9][14].getBlock());
    for(int j=0; j < rows; j++ ){
        for (int i=0; i< cols; i++){
            target->draw(grid[i][j].getBlock());
        }
    }

    LetterBlock a("A");
    a.setPosition(sf::Vector2f(300,300));

    //a.render(target);
    
}
