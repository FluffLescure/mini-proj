

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
    logsFrame_ = sf::RectangleShape({213, 324});
    logsFrame_.setPosition({53, 162});
    logsFrame_.setOutlineColor({125, 125, 125});
    logsFrame_.setOutlineThickness(3);
    logsFrame_.setFillColor({0, 0, 0, 0}); 
}

void GameLogs::initTitle() {
    title_.setString("STATS : 0");
    title_.setCharacterSize(30);
    title_.setFillColor(sf::Color::White);
    title_.setFont(*Config::getInstance()->font_);
    title_.setOrigin({title_.getGlobalBounds().getSize().x / 2.f + title_.getLocalBounds().getPosition().x,0}); // center alignment
    title_.setPosition({158, 162});
}

void GameLogs::initLogs() {
    for (uint8_t i = 0; i < 10; i++){
        logs_[i].setString("");
        logs_[i].setCharacterSize(18);
        logs_[i].setFillColor(sf::Color::White);
        logs_[i].setFont(*Config::getInstance()->font_);
    }
}

void GameLogs::initPoints() {
    for (uint8_t i = 0; i < 10; i++){
        points_[i].setString("");
        points_[i].setCharacterSize(18);
        points_[i].setFillColor(sf::Color::White);
        points_[i].setFont(*Config::getInstance()->font_);
    }
}



void GameLogs::emplace(const std::string& word){
    // Updates the title with the current count of found words 
    count_++;
    title_.setString("STATS : " + std::to_string(count_));
    emplaceLog(word);
    emplacePoints(word);
}

void GameLogs::emplaceLog(const std::string& word) {
    // Shifts the logs down and adds the new word to the top
    for(uint8_t i = 9; i > 0; i--) {
        logs_[i].setString(logs_[i - 1].getString().toAnsiString());
        logs_[i].setPosition({70, 220 + i * (logs_[i].getGlobalBounds().height + 11)});
    }

    logs_[0].setString(word);
    logs_[0].setPosition({70, 220});
}

void GameLogs::emplacePoints(const std::string& word) {
    // Calculates the points based on the word size
    std::string point = std::to_string((int)std::pow(word.size(), 3));

    // Shifts the points down and adds the new points to the top
    for(uint8_t i = 9; i > 0; i--) {
        points_[i].setString(points_[i - 1].getString().toAnsiString());
        points_[i].setOrigin({points_[i].getGlobalBounds().width, 0}); // left alignmnet
        points_[i].setPosition({243, 220 + i * (points_[i].getGlobalBounds().height + 11)});
    }

    points_[0].setString(point);
    points_[0].setOrigin({points_[0].getGlobalBounds().width, 0}); // left alignment
    points_[0].setPosition({243, 220});
}



void GameLogs::render(sf::RenderTarget *target) const {
    target->draw(logsFrame_); 
    target->draw(title_);

    //renders the logs and points
    for(uint8_t i = 0; i < 10; i++){
        target->draw(logs_[i]);
        target->draw(points_[i]);
    }
}
