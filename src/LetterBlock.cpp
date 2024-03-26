#include "../headers/LetterBlock.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>




void LetterBlock::display(bool visible) {
    sf::Color block_color = block.getFillColor();

    // If true then alpha value is 255, else alpha is 0
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
    std::cout << "built" << std::endl;
    initBlock();
    initLetter(str);
}

LetterBlock::LetterBlock() {
    std::cout << "Constructeur blanc" << std::endl;
    initBlock();
    initLetter("D");
}

void LetterBlock::initBlock() {
    block = sf::RectangleShape(sf::Vector2f(33.6,32.4));
    block.setFillColor(sf::Color(175,175,175));
    block.setOutlineColor(sf::Color(75,75,75));
    block.setOutlineThickness(1);  
}



void LetterBlock::initLetter(std::string str) {
    std::cout << "initialisation" << std::endl;
    
    letter.setString(str);
    letter.setCharacterSize(24);
    letter.setFillColor(sf::Color::Black);
    if(!font.loadFromFile("ressources/Lato-Black.ttf")){
        abort();
    }
    letter.setFont(font);

}

void LetterBlock::setPosition(sf::Vector2f pos) {
    block.setPosition(pos);
    letter.setOrigin(sf::Vector2f(0,0));
    letter.setPosition(pos);
}   

void LetterBlock::render(sf::RenderTarget *target) {
    target->draw(block);

    std::cout << "render LetterBlock" << std::endl;
     
    target->draw(letter); // doesn't work for some code fucked mangling reason
}

