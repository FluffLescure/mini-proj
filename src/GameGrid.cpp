#include "../headers/GameGrid.hpp"
#include <iostream>

void GameGrid::gridTick() {
    bool blocks_moved = false;
    for (int8_t i = 0; i < cols; i++) {
        for (int8_t j = rows - 2; j >= 0; j--) {
            if (grid[i][j].isFalling()) {
                blocks_moved = grid[i][j].move(grid, Down);
            }
            
            if(!grid[i][j+1].isHidden() && !grid[i][j].isHidden()) {
                grid[i][j].setState(Grounded);
                grid[i][j].setColor(sf::Color::Red);
            }
        }
    }

    if(!blocks_moved && grid[5][0].isHidden()) {
        blockDisplay({5,0},true);
        grid[5][0].setState(Falling);
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

void GameGrid::blockDisplay(sf::Vector2u coord, bool visible) {
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

    input = new Input();
    
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

void GameGrid::blockTick() {
    bool moved = false;

    for (int8_t i = 0; i < cols; i++) {
        for (int8_t j = rows - 1; j >= 0; j--) {
            if(!grid[i][j].isHidden() && grid[i][j].isFalling() && !moved){
                if(input->getDirection() == Down && j < 14){
                    moved = grid[i][j].move(grid, Down);
                }
                if(input->getDirection() == Left && i > 0){
                    moved = grid[i][j].move(grid, Left);
                }
                if(input->getDirection() == Right && i < 9){
                    moved = grid[i][j].move(grid, Right);
                } 
                if(!grid[i][14].isHidden() && grid[i][14].getState() != Grounded) {
                    grid[i][14].setState(Grounded);
                    grid[i][14].setColor(sf::Color::Red);
                }  
            }
        }
    }

}


void GameGrid::update() {
    input->pollEvent();

    if(!(tick % 5)) {
        blockTick();
    }
    if(tick == 60) {
        gridTick();
        tick = 0;
    }
    tick++;
}