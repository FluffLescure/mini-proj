

#include<stdlib.h>
#include<iostream>

#include "../headers/LetterBlock.hpp"
#include "../headers/Config.hpp"


LetterBlock::LetterBlock(const char& str) {
    initBlock();
    initLetter(str);
}

void LetterBlock::initBlock() {
    block_ = sf::RectangleShape(Config::getInstance()->block_size_);
    block_.setFillColor({175,175,175});
    block_.setOutlineColor({75,75,75});
    block_.setOutlineThickness(1);  
    state_ = State::Fixed;
}

void LetterBlock::initLetter(const char& str) {
    letter_.setString(str);
    letter_.setCharacterSize(24);
    letter_.setFillColor(sf::Color::Black);
    letter_.setFont(*Config::getInstance()->font_);
}



void LetterBlock::operator=(const LetterBlock& block_) {
    // Block colors, letter and state are transfered
    this->block_.setFillColor(block_.getBlock().getFillColor());
    this->block_.setOutlineColor(block_.getBlock().getOutlineColor());
    this->letter_.setString(block_.getLetter().getString());
    this->letter_.setFillColor(block_.getLetter().getFillColor());
    centerLetter(); // guarantees that the new letter is centered
    state_ = block_.getState();
}

void LetterBlock::centerLetter() {
    letter_.setOrigin(letter_.getGlobalBounds().getSize() / 2.f + letter_.getLocalBounds().getPosition());
    letter_.setPosition(block_.getPosition() + block_.getSize() / 2.f);
}



void LetterBlock::setPosition(const sf::Vector2f& pos) {
    block_.setPosition(pos);
    centerLetter();
}  



const sf::Vector2u LetterBlock::getPosition(const Blockgrid& grid) const {
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



const bool LetterBlock::isState(const State& state) const {
    if(this->state_ == state)
        return true;
    return false;
}



const bool LetterBlock::isHidden() const {
    sf::Color col = block_.getFillColor();
    if (col.a == 50)
        return true;
    else
        return false;
}



const bool LetterBlock::move(Blockgrid &grid, const Direction& direction) const{
    sf::Vector2u pos = getPosition(grid);
    uint8_t rows = Config::gamegrid_rows_;
    uint8_t cols = Config::gamegrid_cols_;
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



void LetterBlock::display(const bool& visible) {
    //retrieves the current block colors
    sf::Color block_color = block_.getFillColor();
    sf::Color letter_color = letter_.getFillColor();    

    // If true then alpha value is 255, else hide
    if (visible){
        block_color.a = 255;
        letter_color.a = 255;
    }
    else {
        block_color = sf::Color(175, 175, 175, 50); 
        letter_color.a = 0;
    }

    block_.setFillColor(block_color);
    letter_.setFillColor(letter_color);
}



void LetterBlock::render(sf::RenderTarget *target) const {
    target->draw(block_);
    target->draw(letter_);
}