#include "../headers/GameDisplay.hpp"

#include <fstream>

void GameDisplay::initLayout() {
    
    //Reads map file and retrieve cooridnates of the points used to draw the layout
    std::ifstream file("ressources/layout.map"); 

    std::vector<sf::Vector2f> layoutPoints;

    float x,y;
    while(file >> x >> y) {
        layoutPoints.push_back(sf::Vector2f(x,y)); 
    }

    file.close();

    // Layout points are assimilited into a VertexArray to create a singular custom drawwable
    layout = sf::VertexArray(sf::Quads,layoutPoints.size());

    for (size_t i = 0; i < layoutPoints.size(); ++i) {
        layout[i].position = layoutPoints[i];
    }
}

void GameDisplay::render(sf::RenderTarget *target) {
    target->draw(layout); // renders to window
}

GameDisplay::GameDisplay() {
    initLayout();
}