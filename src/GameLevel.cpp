
#include<sstream>
#include<fstream>
#include<iostream>

#include "../headers/GameLevel.hpp"
#include "../headers/Config.hpp"


GameLevel::GameLevel() {
    speed = 30;
    initColorschemes();
    initFrames();
    initText();
}

void GameLevel::initColorschemes() {
    std::ifstream file(Config::getInstance()->colorscheme_file);
    std::string theme, type, color_str;


    while(file >> theme >> type >> color_str){
        // Convert hex string to an integer value before creating a color object
        sf::Color color = sf::Color(std::stoul(color_str, nullptr, 16));

        // Necessary convertion to index the colorScheme array and avoid exception error
        int theme_val = theme.back() - '0';
        colorScheme[theme_val].emplace(type, color);
    }

    Config::getInstance()->colorScheme = colorScheme[0];
}

void GameLevel::initFrames() {
    stageFrame = sf::RectangleShape({160, 54});
    stageFrame.setPosition({106.6, 54});
    stageFrame.setOutlineColor({125, 125, 125});
    stageFrame.setOutlineThickness(3);
    stageFrame.setFillColor({0, 0, 0, 0}); 

    levelFrame = sf::RectangleShape({186.6, 54});
    levelFrame.setPosition({693.3, 378});
    levelFrame.setOutlineColor({125, 125, 125});
    levelFrame.setOutlineThickness(3);
    levelFrame.setFillColor({0, 0, 0, 0}); 
}

void GameLevel::initText() {
    stageText.setString("STAGE       1");
    stageText.setCharacterSize(24);
    stageText.setFillColor(sf::Color::White);
    stageText.setFont(*(Config::getInstance()->font));
    stageText.setOrigin({0, stageText.getGlobalBounds().height / 2.f + stageText.getLocalBounds().getPosition().y}); // right center alignment
    stageText.setPosition({123.3, 81});

    levelText.setString("LEVEL            1");
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setFont(*(Config::getInstance()->font));
    levelText.setOrigin({0, levelText.getGlobalBounds().height / 2.f + levelText.getLocalBounds().getPosition().y}); // right center alignment
    levelText.setPosition({710, 405});
}


void GameLevel::levelUp() {
    static int lvl = 0;
    const int scheme = Config::levelSpeed[9-lvl] - 2;
    speed -= Config::levelSpeed[lvl];

    Config::getInstance()->colorScheme = colorScheme[scheme];

    lvl++;
    levelText.setString("LEVEL            " + std::to_string(lvl));
    stageText.setString("Stage       " + std::to_string( scheme + 1 ));
}


void GameLevel::render(sf::RenderTarget *target) const {
    target->draw(stageFrame);
    target->draw(levelFrame);

    target->draw(stageText);
    target->draw(levelText);
}