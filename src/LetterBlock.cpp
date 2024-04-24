

#include<stdlib.h>
#include<iostream>

#include "../headers/LetterBlock.hpp"
#include "../headers/Config.hpp"


LetterBlock::LetterBlock(char str) {
    initBlock();
    initLetter(str);
}

void LetterBlock::initBlock() {
    block = sf::RectangleShape(Config::getInstance()->block_size);
    block.setFillColor({175,175,175});
    block.setOutlineColor({75,75,75});
    block.setOutlineThickness(1);  
    state = State::Fixed;
}

void LetterBlock::initLetter(char str) {
    letter.setString(str);
    letter.setCharacterSize(24);
    letter.setFillColor(sf::Color::Black);
    letter.setFont(*(Config::getInstance()->font));
}



void LetterBlock::operator=(LetterBlock& block) {
    // Block colors, letter and state are transfered
    this->block.setFillColor(block.getBlock().getFillColor());
    this->block.setOutlineColor(block.getBlock().getOutlineColor());
    this->letter.setString(block.getLetter().getString());
    this->letter.setFillColor(block.getLetter().getFillColor());
    centerLetter(); // guarantees that the new letter is centered
    state = block.getState();
}

void LetterBlock::centerLetter() {
    letter.setOrigin(letter.getGlobalBounds().getSize() / 2.f + letter.getLocalBounds().getPosition());
    letter.setPosition(block.getPosition() + block.getSize() / 2.f);
}



void LetterBlock::setPosition(sf::Vector2f pos) {
    block.setPosition(pos);
    centerLetter();
}  



sf::Vector2u LetterBlock::getPosition(const Blockgrid& grid) const {
    // Runs throught the entire the grid comparing the memory address of each block 
    // with the current one to find its coordinates
    for (uint8_t i = 0; i < grid.size(); i++) {
        for (uint8_t j = 0; j < grid[i].size(); j++) {
            if (&grid[i][j] == this) {
                return {i, j};
            }
        }
    }
    return sf::Vector2u(-1,-1); // if not found returns (-1, -1)
}



bool LetterBlock::isState(State state) {
    if(this->state == state)
        return true;
    return false;
}



bool LetterBlock::isHidden() {
    sf::Color col = block.getFillColor();
    if (col.a == 50)
        return true;
    else
        return false;
}



bool LetterBlock::move(Blockgrid &grid, Direction direction){
    sf::Vector2u pos = getPosition(grid);
    uint8_t rows = Config::getInstance()->gamegrid_rows;
    uint8_t cols = Config::getInstance()->gamegrid_cols;
    uint8_t i = pos.x, j = pos.y;

    switch(direction) {
        case Down:
            // If block beneath is hidden then move
            if (j < rows - 1 && grid[i][j + 1].isHidden() ) {
                grid[i][j + 1] = grid[i][j];
                grid[i][j].display(false);
                grid[i][j].setLetter(' ');
                grid[i][j].setState(State::Fixed);
                return true;

            }
            return false;

        case Left:
            // If block on the left is hidden then move
            if ( i > 0 && grid[i - 1][j].isHidden()) {
                grid[i - 1][j] = grid[i][j];
                grid[i][j].display(false);
                grid[i][j].setLetter(' ');
                grid[i][j].setState(State::Fixed);
                return true;
            }
            return false;
            
        case Right:
            // If block on the right is hidden then move
            if (i < cols - 1 && grid[i + 1][j].isHidden()) {
                grid[i + 1][j] = grid[i][j];
                grid[i][j].display(false);
                grid[i][j].setLetter(' ');
                grid[i][j].setState(State::Fixed);
                return true;
            }
            return false;

        default:
            return false;
    }
}



void LetterBlock::display(bool visible) {
    //retrieves the current block colors
    sf::Color block_color = block.getFillColor();
    sf::Color letter_color = letter.getFillColor();    

    // If true then alpha value is 255, else alpha is 50
    if (visible){
        block_color.a = 255;
        letter_color.a = 255;
    }
    else {
        block_color.a = 50; 
        letter_color.a = 0;
    }

    block.setFillColor(block_color);
    letter.setFillColor(letter_color);
}



void LetterBlock::render(sf::RenderTarget *target) {
    target->draw(block);
    target->draw(letter);
}