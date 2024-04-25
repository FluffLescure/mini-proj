
#include<fstream>
#include<iostream>

#include "../headers/Config.hpp"


// First instance of Config is populated before Config::getInstance()
// is called in runtime
Config* Config::instance = new Config();

constexpr Config::Config() {
    loadFonts();
    loadTextures();
    loadLayout();
    loadWordlist();
}

constexpr void Config::loadFonts() {
    font = new sf::Font();

    if(!font->loadFromFile(font_file)) {
        std::cout << "ERROR: Failed to load fonts : " << font_file << std::endl;
        abort();
    }
}

constexpr void Config::loadTextures() {
    layoutTex = new sf::Texture();
    if(!layoutTex->loadFromFile(texture_file)) {
        std::cout << "ERROR: Failed to load texture file : " << texture_file << std::endl;
        abort();
    }
}

constexpr void Config::loadLayout() {
    float x,y;
    std::ifstream file(layout_file);

    // Loads x and y coords of the layout
    while (file >> x >> y) {
        layoutPoints.push_back({x, y});
    }

    file.close();
}

constexpr void Config::loadWordlist() {
    std::string word;
    std::ifstream file(wordlist_file);

    while(file >> word) {
        // Capitalises every word in the list
        for(char &c : word)
            c = std::toupper(c);

        wordlist.push_back(word);
    }

    file.close();
}

Config* Config::getInstance() {
    if(!instance)
        instance = new Config;
    return instance;
}


constexpr Config::~Config() {
    delete font;
    delete layoutTex;
}












