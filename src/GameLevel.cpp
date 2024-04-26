
#include<sstream>
#include<fstream>
#include<iostream>

#include "../headers/GameLevel.hpp"
#include "../headers/Config.hpp"


GameLevel::GameLevel() {
    speed_ = 30;
    initColorschemes();
    initFrames();
    initText();
}

void GameLevel::initColorschemes() {
    std::ifstream file(Config::getInstance()->colorscheme_file_);
    std::string theme, type, color_str;

    // Reads the color scheme file and creates a map of color objects

    while(file >> theme >> type >> color_str){
        // Convert hex string to an integer value before creating a color object
        sf::Color color = sf::Color(std::stoul(color_str, nullptr, 16));

        // Necessary convertion to index the colorScheme array and avoid exception error
        int theme_val = theme.back() - '0';
        colorScheme_[theme_val].emplace(type, color);
    }

    Config::getInstance()->colorScheme_ = colorScheme_[0];
}

void GameLevel::initFrames() {
    stageFrame_ = sf::RectangleShape({160, 54});
    stageFrame_.setPosition({106.6, 54});
    stageFrame_.setOutlineColor({125, 125, 125});
    stageFrame_.setOutlineThickness(3);
    stageFrame_.setFillColor({0, 0, 0, 0}); 

    levelFrame_ = sf::RectangleShape({186.6, 54});
    levelFrame_.setPosition({693.3, 378});
    levelFrame_.setOutlineColor({125, 125, 125});
    levelFrame_.setOutlineThickness(3);
    levelFrame_.setFillColor({0, 0, 0, 0}); 
}

void GameLevel::initText() {
    stageText_.setString("STAGE       1");
    stageText_.setCharacterSize(24);
    stageText_.setFillColor(sf::Color::White);
    stageText_.setFont(*Config::getInstance()->font_);
    stageText_.setOrigin({0, stageText_.getGlobalBounds().height / 2.f + stageText_.getLocalBounds().getPosition().y}); // right center alignment
    stageText_.setPosition({123.3, 81});

    levelText_.setString("LEVEL            1");
    levelText_.setCharacterSize(24);
    levelText_.setFillColor(sf::Color::White);
    levelText_.setFont(*Config::getInstance()->font_);
    levelText_.setOrigin({0, levelText_.getGlobalBounds().height / 2.f + levelText_.getLocalBounds().getPosition().y}); // right center alignment
    levelText_.setPosition({710, 405});
}


void GameLevel::levelUp() {
    // Tracks the current level
    static int lvl = 0;

    // The color scheme is changed every time the value of levelspeed is different
    const int scheme = Config::levelSpeed_[9-lvl] - 2;
    speed_ -= Config::levelSpeed_[lvl];

    Config::getInstance()->colorScheme_ = colorScheme_[scheme];

    lvl++;
    levelText_.setString("LEVEL            " + std::to_string(lvl));
    stageText_.setString("Stage       " + std::to_string( scheme + 1 ));
}


void GameLevel::render(sf::RenderTarget *target) const {
    target->draw(stageFrame_);
    target->draw(levelFrame_);

    target->draw(stageText_);
    target->draw(levelText_);
}