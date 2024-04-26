
#include<fstream>
#include<iostream>

#include "../headers/Config.hpp"


// First instance of Config is populated before Config::getInstance() is called
Config* Config::instance_ = new Config();



Config::Config() {
    loadFonts();
    loadTextures();
    loadLayout();
    loadWordlist();
}

void Config::loadFonts() {
    font_ = new sf::Font();

    if(!font_->loadFromFile(font_file_)) {
        std::cout << "ERROR: Failed to load fonts : " << font_file_ << std::endl;
        abort();
    }
}

void Config::loadTextures() {
    layoutTex_ = new sf::Texture();
    if(!layoutTex_->loadFromFile(texture_file_)) {
        std::cout << "ERROR: Failed to load texture file : " << texture_file_ << std::endl;
        abort();
    }
}

void Config::loadLayout() {
    float x,y;
    std::ifstream file(layout_file_);

    // Loads x and y coords of the layout
    while (file >> x >> y) {
        layoutPoints_.push_back({x, y});
    }

    file.close();
}

void Config::loadWordlist() {
    std::string word;
    std::ifstream file(wordlist_file_);

    while(file >> word) {
        // Capitalises every word in the list
        for(char &c : word)
            c = std::toupper(c);

        wordlist_.push_back(word);
    }

    file.close();
}




Config::~Config() {
    delete font_;
    delete layoutTex_;
}












