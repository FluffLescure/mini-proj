

#include<iostream>

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
    letter.setString(randLetter());
    letter.setCharacterSize(50);
    letter.setFillColor(sf::Color::White);
    letter.setFont(*(Config::getInstance()->font));
    letter.setOrigin({letter.getGlobalBounds().getSize().x / 2.f + letter.getLocalBounds().getPosition().x,0});
    letter.setPosition(sf::Vector2f(760,283));
}



void GameLetter::render(sf::RenderTarget *target){
    target->draw(letterFrame);
    target->draw(title);
    target->draw(letter);
}


char GameLetter::getLetter() {
    return letter.getString().toAnsiString().c_str()[0];
}



void GameLetter::changeLetter() {
    letter.setString(randLetter());
    letter.setOrigin({letter.getGlobalBounds().getSize().x / 2.f + letter.getLocalBounds().getPosition().x,0});
}

char GameLetter::randLetter() {
    int max = 0, min = 0;
    for (int i = 0; i < 26; i++)
        max += Config::getInstance()->generator_weights[i];

    int r = ((double) rand() / (RAND_MAX + 1)) * (max - min + 1) + min;
    int letter, sum = 0;

    for(letter = 0; r > sum; letter++)
        sum += Config::getInstance()->generator_weights[letter];

    return (char) 'A' +  --letter;
}










