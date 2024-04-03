
#include<fstream>
#include<iostream>

#include "../headers/Config.hpp"


// First instance of Config is set null before getInstance() is called
Config* Config::instance = nullptr;


Config::Config() {
    loadFonts();
    loadTextures();
    loadLayout();
    loadWordlist();
}

Config::~Config() {
    delete font;
    delete layoutTex;
}


Config* Config::getInstance() {
    // if there isn't yet any instance, create one, else return the current instance
    if (instance == nullptr)
        instance = new Config();
    return instance;
}

void Config::loadTextures() {
    layoutTex = new sf::Texture();
    if(!layoutTex->loadFromFile(texture_file)) {
        std::cout << "ERROR: Failed to load " << texture_file << std::endl;
        abort();
    }
}

void Config::loadLayout() {
    float x,y;
    std::ifstream file(layout_file);

    // Loads x and y coords to a map
    while (file >> x >> y) {
        layoutPoints.push_back(sf::Vector2f(x, y));
    }

    file.close();
}

void Config::loadFonts() {
    font = new sf::Font();

    if(!font->loadFromFile(font_file)) {
        std::cout << "ERROR: Failed to load " << font_file << std::endl;
        abort();
    }
}

void Config::loadWordlist() {
    std::string word;
    std::ifstream file(wordlist_file);

    while(file >> word) {

        for(char &c : word)
            c = std::toupper(c);

        wordlist.push_back(word);
    }

    file.close();
}


