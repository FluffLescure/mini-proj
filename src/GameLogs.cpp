

#include<iostream>
#include<cmath>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "../headers/GameLogs.hpp"
#include "../headers/Config.hpp"


GameLogs::GameLogs(){
    initFrame();
    initTitle();
    initLogs();
    initPoints();
}

void GameLogs::initFrame() {
    logsFrame = sf::RectangleShape({213, 324});
    logsFrame.setPosition({53, 162});
    logsFrame.setOutlineColor({125, 125, 125});
    logsFrame.setOutlineThickness(3);
    logsFrame.setFillColor({0, 0, 0, 0}); 
}

void GameLogs::initTitle() {
    title.setString("STATS : 0");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setFont(*Config::getInstance()->font);
    title.setOrigin({title.getGlobalBounds().getSize().x / 2.f + title.getLocalBounds().getPosition().x,0}); // center alignment
    title.setPosition({158, 162});
}

void GameLogs::initLogs() {
    for (uint8_t i = 0; i < 10; i++){
        logs[i].setString("");
        logs[i].setCharacterSize(18);
        logs[i].setFillColor(sf::Color::White);
        logs[i].setFont(*Config::getInstance()->font);
    }
}

void GameLogs::initPoints() {
    for (uint8_t i = 0; i < 10; i++){
        points[i].setString("");
        points[i].setCharacterSize(18);
        points[i].setFillColor(sf::Color::White);
        points[i].setFont(*Config::getInstance()->font);
    }
}



void GameLogs::emplace(const std::string& word){
    // Updates the title with the current count of found words
    static uint8_t count = 1;


    title.setString("STATS : " + std::to_string(count));
    emplaceLog(word);
    emplacePoints(word);

    count++;
}

void GameLogs::emplaceLog(const std::string& word) {
    // Shifts the logs down and adds the new word to the top
    for(uint8_t i = 9; i > 0; i--) {
        logs[i].setString(logs[i - 1].getString().toAnsiString());
        logs[i].setPosition({70, 220 + i * (logs[i].getGlobalBounds().height + 11)});
    }

    logs[0].setString(word);
    logs[0].setPosition({70, 220});
}

void GameLogs::emplacePoints(const std::string& word) {
    // Calculates the points based on the word size
    std::string point = std::to_string((int)std::pow(word.size(), 3));

    // Shifts the points down and adds the new points to the top
    for(uint8_t i = 9; i > 0; i--) {
        points[i].setString(points[i - 1].getString().toAnsiString());
        points[i].setOrigin({points[i].getGlobalBounds().width, 0}); // left alignmnet
        points[i].setPosition({243, 220 + i * (points[i].getGlobalBounds().height + 11)});
    }

    points[0].setString(point);
    points[0].setOrigin({points[0].getGlobalBounds().width, 0}); // left alignment
    points[0].setPosition({243, 220});
}



void GameLogs::render(sf::RenderTarget *target) const {
    target->draw(logsFrame); 
    target->draw(title);

    //renders the logs and points
    for(uint8_t i = 0; i < 10; i++){
        target->draw(logs[i]);
        target->draw(points[i]);
    }
}
