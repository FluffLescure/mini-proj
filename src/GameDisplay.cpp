#include "../headers/GameDisplay.hpp"

#include <fstream>

void GameDisplay::initLayout() {
    
    std::ifstream file("ressources/layout.map");

    std::vector<sf::Vector2f> layoutPoints;

    float x,y;
    while(file >> x >> y) {
        layoutPoints.push_back(sf::Vector2f(x,y));
    }

    file.close();

    layout = sf::VertexArray(sf::Quads,layoutPoints.size());

    for (size_t i = 0; i < layoutPoints.size(); ++i) {
        layout[i].position = layoutPoints[i];
    }
}

void GameDisplay::render(sf::RenderTarget *target) {
    target->draw(layout);
}

GameDisplay::GameDisplay() {
    initLayout();
}