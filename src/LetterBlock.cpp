#include "../headers/LetterBlock.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <../headers/Config.hpp>



void LetterBlock::display(bool visible) {
    sf::Color block_color = block.getFillColor();

    // If true then alpha value is 255, else alpha is 50
    if (visible)
        block_color.a = 255;
    else
        block_color.a = 50;

    setColor(block_color);
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
    initLetter("X");
}

void LetterBlock::initBlock() {
    block = sf::RectangleShape(sf::Vector2f(33.6,32.4));
    block.setFillColor(sf::Color(175,175,175));
    block.setOutlineColor(sf::Color(75,75,75));
    block.setOutlineThickness(1);  
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

