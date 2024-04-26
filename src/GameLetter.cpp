

#include<iostream>
#include<numeric>


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "../headers/GameLetter.hpp"
#include "../headers/Config.hpp"


GameLetter::GameLetter(){
    initFrame();
    initTitle();
    initLetter();
}

void GameLetter::initFrame() {
    letterFrame_ = sf::RectangleShape({80, 108});
    letterFrame_.setPosition({720, 243});
    letterFrame_.setOutlineColor({125, 125, 125});
    letterFrame_.setOutlineThickness(3);
    letterFrame_.setFillColor({0, 0, 0, 0}); 
}

void GameLetter::initTitle() {
    title_.setString("NEXT");
    title_.setCharacterSize(20);
    title_.setFillColor(sf::Color::White);
    title_.setFont(*(Config::getInstance()->font_));
    title_.setOrigin({title_.getGlobalBounds().getSize().x / 2.f + title_.getLocalBounds().getPosition().x,0});
    title_.setPosition({760, 243});
}

void GameLetter::initLetter() {
    letter_.setCharacterSize(50);
    letter_.setFillColor(sf::Color::White);
    letter_.setFont(*(Config::getInstance()->font_));
    letter_.setPosition({760, 283});
    changeLetter();
}



void GameLetter::render(sf::RenderTarget *target) const {
    target->draw(letterFrame_);
    target->draw(title_);
    target->draw(letter_);
}


const char GameLetter::getLetter() {
    return letter_.getString().toAnsiString().c_str()[0];
}



void GameLetter::changeLetter() {
    // Sets the letter to a random char
    char c = randLetter();
    letter_.setString(c);

    letter_.setOrigin({letter_.getGlobalBounds().getSize().x / 2.f + letter_.getLocalBounds().getPosition().x,0}); // recenters the letter
}

const char GameLetter::randLetter() {
    static const int min = 0;
    static const int max = std::accumulate(std::begin(Config::generator_weights_), std::end(Config::generator_weights_), 0);

    // Generates a random number between min and max
    static int r;
    r = ((double) rand() / (RAND_MAX + 1)) * (max - min + 1) + min;

    static int letter, sum;

    // Finds the letter that corresponds to the random number
    for(letter = 0, sum=0; r > sum; letter++)
        sum += Config::generator_weights_[letter];

    return (char) 'A' +  --letter;
}










