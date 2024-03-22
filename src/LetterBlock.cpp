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