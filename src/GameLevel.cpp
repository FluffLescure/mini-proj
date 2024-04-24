
#include<sstream>
#include<fstream>
#include<iostream>

#include "../headers/GameLevel.hpp"
#include "../headers/Config.hpp"


GameLevel::GameLevel() {
    speed = 30;
    initColorschemes();
}

void GameLevel::initColorschemes() {
    std::ifstream file(Config::getInstance()->colorscheme_file);
    std::string theme, type, color_str;


    while(file >> theme >> type >> color_str){
        sf::Color color = sf::Color(std::stoul(color_str + "FF", nullptr, 16));
        std::cout << color.toInteger() << std::endl;
        int theme_val = theme.back() - '0';
        colorScheme[theme_val].emplace(type, color);
    }

    Config::getInstance()->colorScheme = colorScheme[3];
}

int GameLevel::getSpeed() const {
    return 0;
}

void GameLevel::levelUp() {

}