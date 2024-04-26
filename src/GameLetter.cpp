

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
    letterFrame = sf::RectangleShape({80, 108});
    letterFrame.setPosition({720, 243});
    letterFrame.setOutlineColor({125, 125, 125});
    letterFrame.setOutlineThickness(3);
    letterFrame.setFillColor({0, 0, 0, 0}); 
}

void GameLetter::initTitle() {
    title.setString("NEXT");
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::White);
    title.setFont(*(Config::getInstance()->font));
    title.setOrigin({title.getGlobalBounds().getSize().x / 2.f + title.getLocalBounds().getPosition().x,0});
    title.setPosition({760, 243});
}

void GameLetter::initLetter() {
    letter.setCharacterSize(50);
    letter.setFillColor(sf::Color::White);
    letter.setFont(*(Config::getInstance()->font));
    letter.setPosition({760, 283});
    changeLetter();
}



void GameLetter::render(sf::RenderTarget *target) const {
    target->draw(letterFrame);
    target->draw(title);
    target->draw(letter);
}


const char GameLetter::getLetter() {
    return letter.getString().toAnsiString().c_str()[0];
}



void GameLetter::changeLetter() {
    // Sets the letter to a random char
    char c = randLetter();
    letter.setString(c);

    letter.setOrigin({letter.getGlobalBounds().getSize().x / 2.f + letter.getLocalBounds().getPosition().x,0}); // recenters the letter
}

const char GameLetter::randLetter() {
    static const int min = 0;
    static const int max = std::accumulate(std::begin(Config::generator_weights), std::end(Config::generator_weights), 0);

    // Generates a random number between min and max
    static int r;
    r = ((double) rand() / (RAND_MAX + 1)) * (max - min + 1) + min;

    static int letter, sum;

    // Finds the letter that corresponds to the random number
    for(letter = 0, sum=0; r > sum; letter++)
        sum += Config::generator_weights[letter];

    return (char) 'A' +  --letter;
}










