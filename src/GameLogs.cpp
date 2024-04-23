

#include<iostream>
#include<cmath>

#include "../headers/GameLogs.hpp"
#include "../headers/Config.hpp"


GameLogs::GameLogs(){
    initFrame();
    initTitle();
    initLogs();
    initPoints();
}

void GameLogs::initFrame() {
    logsFrame = sf::RectangleShape(sf::Vector2f(213, 324));
    logsFrame.setPosition(sf::Vector2f(53, 162));
    logsFrame.setOutlineColor(sf::Color(125, 125, 125));
    logsFrame.setOutlineThickness(3);
    logsFrame.setFillColor(sf::Color(0, 0, 0, 0)); 
}

void GameLogs::initTitle() {
    title.setString("STATS");
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
        logs[i].setString("");
        logs[i].setCharacterSize(18);
        logs[i].setFillColor(sf::Color::White);
        logs[i].setFont(*(Config::getInstance()->font));
        text_size = sf::Vector2f(logs[i].getGlobalBounds().getSize() + logs[i].getLocalBounds().getPosition()); //size of the text
        logs[i].setOrigin( logs[i].getLocalBounds().getPosition());
        logs[i].setPosition(sf::Vector2f(63,220+i*(text_size.y+5)));
    }
}

void GameLogs::initPoints() {
    sf::Vector2f text_size;
    points = std::vector<sf::Text>(10);

    for (int i=0;i<10;i++){
        points[i].setString("");
        points[i].setCharacterSize(18);
        points[i].setFillColor(sf::Color::White);
        points[i].setFont(*(Config::getInstance()->font));
        text_size = sf::Vector2f(points[i].getGlobalBounds().getSize() + points[i].getLocalBounds().getPosition()); //size of the text
        points[i].setOrigin( sf::Vector2f(points[i].getGlobalBounds().getSize().x ,0) + points[i].getLocalBounds().getPosition());
        points[i].setPosition(sf::Vector2f(213,220+i*(text_size.y+5)));


        // letter.setOrigin(letter.getGlobalBounds().getSize() / 2.f + letter.getLocalBounds().getPosition());
    }
}

void GameLogs::render(sf::RenderTarget *target){
    target->draw(logsFrame); // renders the frame
    target->draw(title);
    for(int i = 0; i<10; i++){
        target->draw(logs[i]);
        target->draw(points[i]);
    }
}

void GameLogs::emplaceLog(std::string word) {
    for(int i = 9; i > 0; i--) {
        logs[i].setString(logs[i - 1].getString().toAnsiString());
        sf::Vector2f text_size = logs[i].getGlobalBounds().getSize() + logs[i].getLocalBounds().getPosition(); //size of the text
        logs[i].setPosition({63, 220 + i * (text_size.y + 5)});
    }
    logs[0].setString(word);
}

void GameLogs::emplacePoints(std::string word) {
    std::string point = std::to_string((int)std::pow(word.size(), 3));

    for(int i = 9; i > 0; i--) {
        points[i].setString(points[i - 1].getString().toAnsiString());
        sf::Vector2f text_size = points[i].getGlobalBounds().getSize() + points[i].getLocalBounds().getPosition(); //size of the text
        points[i].setPosition({213, 220 + i * (text_size.y + 5)});
    }
    points[0].setString(point);

}

void GameLogs::emplace(std::string word){
    emplaceLog(word);
    emplacePoints(word);
}