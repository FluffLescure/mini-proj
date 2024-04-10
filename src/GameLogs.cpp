

#include<iostream>

#include "../headers/GameLogs.hpp"
#include "../headers/Config.hpp"


GameLogs::GameLogs(){
    initFrame();
    initTitle();
    initLogs();
}

void GameLogs::initFrame() {
    logsFrame = sf::RectangleShape(sf::Vector2f(213, 324));
    logsFrame.setPosition(sf::Vector2f(53, 162));
    logsFrame.setOutlineColor(sf::Color(125, 125, 125));
    logsFrame.setOutlineThickness(5);
    logsFrame.setFillColor(sf::Color(0, 0, 0, 0)); 
}

void GameLogs::initTitle() {
    title.setString("Stats");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setFont(*(Config::getInstance()->font));
    title.setOrigin(sf::Vector2f(title.getGlobalBounds().getSize().x / 2.f + title.getLocalBounds().getPosition().x,0));
    title.setPosition(sf::Vector2f(158,162));
}

void GameLogs::initLogs() {
    sf::Vector2f text_size;
    logs = std::vector<sf::Text>(10);

    for (int i=0;i<10;i++){
        logs[i].setString("Random");
        logs[i].setCharacterSize(18);
        logs[i].setFillColor(sf::Color::White);
        logs[i].setFont(*(Config::getInstance()->font));
        text_size = sf::Vector2f(logs[i].getGlobalBounds().getSize() + logs[i].getLocalBounds().getPosition()); //size of the text
        logs[i].setPosition(sf::Vector2f(63,220+i*(text_size.y+5)));
    }
}

void GameLogs::render(sf::RenderTarget *target){
    target->draw(logsFrame); // renders the frame
    target->draw(title);
    for(int i = 0; i<10; i++){
        target->draw(logs[i]);
    }
}

void GameLogs::emplaceLog(std::string word) {
    for(int i = 9; i > 0; i--) {
        std::cout << logs[i].getString().toAnsiString().c_str() << std::endl;

        logs[i].setString(logs[i-1].getString().toAnsiString());
    }
    logs[0].setString(word);
}