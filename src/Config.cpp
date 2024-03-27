#include "../headers/Config.hpp"

#include <fstream>
#include <iostream>

Config* Config::instance = nullptr;


Config::Config() {
    loadFonts();
    loadTextures();
    loadLayout();
}

Config::~Config() {
    delete font;
    delete layoutTex;
}


Config* Config::getInstance() {
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


