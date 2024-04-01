#include "../headers/GameGrid.hpp"
#include "../headers/Config.hpp"
#include <iostream>

void GameGrid::gridTick() {
    // This is variable used to determine if the grid has changed or not
    bool blocks_moved = false;

    // Moves the LetterBlocks that are falling 
    for (int8_t i = 0; i < cols; i++) {
        for (int8_t j = rows - 1; j >= 0; j--) {
            if (grid[i][j].isState(Falling))
                blocks_moved = grid[i][j].move(grid, Down);
        }
    }

    // if the grid hasn't changed then add a new falling LetterBlock
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
            grid[i][j].setLetter(' ');
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
    // Pulls the dimensions from the Config
    rows = Config::getInstance()->gamegrid_rows;
    cols = Config::getInstance()->gamegrid_cols;


    // Draws the bounding frame of the grid
    gridBorder = sf::RectangleShape(sf::Vector2f(336, 486));
    gridBorder.setPosition(sf::Vector2f(312, 27));
    gridBorder.setOutlineColor(sf::Color(125, 125, 125));
    gridBorder.setOutlineThickness(5);
    gridBorder.setFillColor(sf::Color(0, 0, 0, 0));
    
    // Creates the 2D grid and fills it with empty LetterBlocks
    grid = Blockgrid(cols, std::vector<LetterBlock>(rows));

    for(int j=0; j < rows; j++ ){
        for (int i=0; i < cols; i++){
            grid[i][j].setPosition(sf::Vector2f(312+33.6*i, 27+32.4*j));
            grid[i][j].display(false);
        }
    }


    
}

GameGrid::GameGrid() {
    initGrid();
    input = new Input();
    dico = new Dictionnary();
}


void GameGrid::render(sf::RenderTarget *target){
    target->draw(gridBorder); // renders the frame

    // Renders each LetterBlock of the grid
    for(int j = 0; j < rows; j++ ){
        for (int i = 0; i< cols; i++){
            grid[i][j].render(target);
        }
    }
}

void GameGrid::blockTick() {
    // Variable used to determine if a block has already been moved.
    // This avoid moving a same block too many times within the loop
    bool moved = false;

    // maybe find a way to clean this up in the future, its too nested
    for (int8_t i = 0; i < cols; i++) {
        for (int8_t j = rows - 1; j >= 0; j--) {
            if(grid[i][j].isState(Falling) && !moved){
                if(input->getDirection() == Down)
                    moved = grid[i][j].move(grid, Down);

                if(input->getDirection() == Left)
                    moved = grid[i][j].move(grid, Left);

                if(input->getDirection() == Right)
                    moved = grid[i][j].move(grid, Right);
            }
            groundBlock(i,j); // checks if every block should be grounded
        }
    }

}


void GameGrid::update() {
    // Retrieves user input
    input->pollEvent();

    if(!(tick % 5)) {
        blockTick();
    }
    if(tick == 30) {
        gridTick();
        tick = 0;
    }
    tick++;
}

void GameGrid::groundBlock(uint8_t i, uint8_t j) {
    // the block isn't falling then don't proceed
    if(!grid[i][j].isState(Falling))
        return; 

    // if its on the last row or if the block under it is grounded, then
    // set the block to grounded
    if(j == rows - 1 || (j < rows - 1 && grid[i][j+1].isState(Grounded))) {
        grid[i][j].setState(Grounded);
        grid[i][j].setColor(sf::Color::Red);
    }
}