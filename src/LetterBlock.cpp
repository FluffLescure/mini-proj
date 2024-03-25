#include "../headers/LetterBlock.hpp"

void LetterBlock::display(bool visible) {
    sf::Color block_color = block.getFillColor();

    // If true then alpha value is 255, else alpha is 0
    if (visible)
        block_color.a = 255;
    else
        block_color.a = 0;

    setColor(block_color);
}

bool LetterBlock::isHidden() {
    sf::Color col = block.getFillColor();
    if (col.a == 0)
        return true;
    else
        return false;
}

LetterBlock::LetterBlock(std::string letter) : letter(letter) {
    block = sf::RectangleShape(sf::Vector2f(33.6,32.4));
    block.setFillColor(sf::Color(175,175,175));
    block.setOutlineColor(sf::Color(75,75,75));
    block.setOutlineThickness(1);
}