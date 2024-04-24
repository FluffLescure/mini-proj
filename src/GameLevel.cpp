
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
    int theme_val;


     std::cout << "loading\n";
    while(file >> theme >> type >> color_str){
        sf::Color color = sf::Color(std::stoul(color_str, nullptr, 16));
        std::cout << color.toInteger() << std::endl;
        theme_val = theme.back();
        std::cout << "done\n";
        colorScheme[theme_val].insert(std::pair(type, color));
        std::cout << "done2\n";
    }

    std::cout << "loaded\n";
    Config::getInstance()->colorScheme = colorScheme[0];
}

int GameLevel::getSpeed() const {
    return 0;
}

void GameLevel::levelUp() {

}