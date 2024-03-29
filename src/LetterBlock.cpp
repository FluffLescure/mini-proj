#include "../headers/LetterBlock.hpp"

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "../headers/Config.hpp"


void LetterBlock::display(bool visible) {
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


bool LetterBlock::isHidden() {
    sf::Color col = block.getFillColor();
    if (col.a == 50)
        return true;
    else
        return false;
}

LetterBlock::LetterBlock(std::string str) {
    initBlock();
    initLetter(str);
}

LetterBlock::LetterBlock() {
    initBlock();
    initLetter("A");
}

void LetterBlock::initBlock() {
    block = sf::RectangleShape(sf::Vector2f(33.6,32.4));
    block.setFillColor(sf::Color(175,175,175));
    block.setOutlineColor(sf::Color(75,75,75));
    block.setOutlineThickness(1);  
    state = Fixed;
}



void LetterBlock::initLetter(std::string str) {
    letter.setString(str);
    letter.setCharacterSize(24);
    letter.setFillColor(sf::Color::Black);
    letter.setFont(*(Config::getInstance()->font));

}

void LetterBlock::setPosition(sf::Vector2f pos) {
    block.setPosition(pos);

    //Found online, allows for centering of letters inside the block
    letter.setOrigin(letter.getGlobalBounds().getSize() / 2.f + letter.getLocalBounds().getPosition());
    letter.setPosition(block.getPosition() + (block.getSize() / 2.f));
}   

void LetterBlock::render(sf::RenderTarget *target) {
    target->draw(block);
    target->draw(letter);
}

void LetterBlock::operator=(LetterBlock& LB) {
    this->block.setFillColor(LB.getBlock().getFillColor());
    this->block.setOutlineColor(LB.getBlock().getOutlineColor());
    this->letter.setString(LB.getLetter().getString());
    this->letter.setFillColor(LB.getLetter().getFillColor());
    state = LB.getState();
}

sf::Vector2u LetterBlock::getPosition(const Blockgrid& grid) const {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (&grid[i][j] == this) {
                return sf::Vector2u(i, j);
            }
        }
    }
    return sf::Vector2u(-1, -1);
}

bool LetterBlock::isFalling() {
    if(state == Falling)
        return true;
    return false;
}

bool LetterBlock::move(Blockgrid &grid, Direction direction){
    sf::Vector2u pos = getPosition(grid);
    int8_t i = pos.x, j = pos.y;

    switch(direction) {
        case Down:
            if (grid[i][j + 1].isHidden() && j < 14) {
                grid[i][j + 1] = grid[i][j];
                grid[i][j].display(false);
                grid[i][j].setState(State::Fixed);
            }
            return true;
        case Left:
            if ( i > 0 && grid[i - 1][j].isHidden()) {
                grid[i - 1][j] = grid[i][j];
                grid[i][j].display(false);
                grid[i][j].setState(State::Fixed);
            }
            return true;
        case Right:
            if (i < 9 && grid[i + 1][j].isHidden()) {
                grid[i + 1][j] = grid[i][j];
                grid[i][j].display(false);
                grid[i][j].setState(State::Fixed);
            }
            return true;
        default:
            return false;
    }
}