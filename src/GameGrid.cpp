#include "../headers/GameGrid.hpp"
#include "../headers/Config.hpp"
#include <iostream>

void GameGrid::gridTick() {
    bool blocks_moved = false;
    for (int8_t i = 0; i < cols; i++) {
        for (int8_t j = rows - 1; j >= 0; j--) {
            if (grid[i][j].isState(Falling))
                blocks_moved = grid[i][j].move(grid, Down);
        }
    }

    if(!blocks_moved && grid[5][0].isHidden()) {
        blockDisplay({5,0},true);
        grid[5][0].setState(State::Falling);
        grid[5][0].randLetter();
    }
}

void GameGrid::blockDestroy(sf::Vector2u posInit, sf::Vector2u span) {
    for (uint8_t j = posInit.y; j < posInit.y + span.y; j++) {
        for (uint8_t i = posInit.x; i < posInit.x + span.x; i++) {
            grid[i][j].display(false);
            grid[i][j].setLetter("");
            grid[i][j].setState(State::Fixed);
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
    Config *config = Config::getInstance(); 
    rows = config->gamegrid_rows;
    cols = config->gamegrid_cols;


    gridBorder = sf::RectangleShape(sf::Vector2f(336, 486));
    gridBorder.setPosition(sf::Vector2f(312, 27));
    gridBorder.setOutlineColor(sf::Color(125, 125, 125));
    gridBorder.setOutlineThickness(5);
    gridBorder.setFillColor(sf::Color(0, 0, 0, 0));
    

    grid = Blockgrid(cols, std::vector<LetterBlock>(rows));

    for(int j=0; j < rows; j++ ){
        for (int i=0; i < cols; i++){
            grid[i][j].setPosition(sf::Vector2f(312+33.6*i, 27+32.4*j));
            grid[i][j].display(false);
        }
    }

    input = new Input();
    
}

GameGrid::GameGrid() {
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
            if(!grid[i][j].isHidden() && grid[i][j].isState(Falling) && !moved){
                if(input->getDirection() == Down)
                    moved = grid[i][j].move(grid, Down);

                if(input->getDirection() == Left)
                    moved = grid[i][j].move(grid, Left);

                if(input->getDirection() == Right)
                    moved = grid[i][j].move(grid, Right);
            }
            groundBlock(i,j);
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

void GameGrid::groundBlock(uint8_t i, uint8_t j) {
    if(!grid[i][j].isState(Falling))
        return;

    if(j < 14 && grid[i][j+1].isState(Grounded)) {
        grid[i][j].setState(Grounded);
        grid[i][j].setColor(sf::Color::Red);
    }

    if(j == 14) {
        grid[i][14].setState(State::Grounded);
        grid[i][14].setColor(sf::Color::Red);
    }
}