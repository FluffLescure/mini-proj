

#include<iostream>
#include<cmath>

#include "../headers/GameLetter.hpp"
#include "../headers/Config.hpp"


GameLetter::GameLetter(){
    initFrame();
    initTitle();
    initLetter();
}

void GameLetter::initFrame() {
    letterFrame = sf::RectangleShape(sf::Vector2f(80, 108));
    letterFrame.setPosition(sf::Vector2f(720, 243));
    letterFrame.setOutlineColor(sf::Color(125, 125, 125));
    letterFrame.setOutlineThickness(3);
    letterFrame.setFillColor(sf::Color(0, 0, 0, 0)); 
}

void GameLetter::initTitle() {
    title.setString("NEXT");
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::White);
    title.setFont(*(Config::getInstance()->font));
    title.setOrigin(sf::Vector2f(title.getGlobalBounds().getSize().x / 2.f + title.getLocalBounds().getPosition().x,0));
    title.setPosition(sf::Vector2f(760,243));
}

void GameLetter::initLetter() {
    letter.setString("?");
    letter.setCharacterSize(50);
    letter.setFillColor(sf::Color::White);
    letter.setFont(*(Config::getInstance()->font));
    letter.setOrigin(sf::Vector2f(letter.getGlobalBounds().getSize().x / 2.f + letter.getLocalBounds().getPosition().x,0));
    letter.setPosition(sf::Vector2f(760,283));
}

void GameLetter::changeLetter(char newLetter){
    letter.setString(newLetter);
    letter.setOrigin(sf::Vector2f(letter.getGlobalBounds().getSize().x / 2.f + letter.getLocalBounds().getPosition().x,0));
}

void GameLetter::centerLetter(){

}



void GameLetter::render(sf::RenderTarget *target){
    target->draw(letterFrame); // renders the frame
    target->draw(title);
    centerLetter();
    target->draw(letter);
}


