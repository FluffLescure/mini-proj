#include "../headers/GameDisplay.hpp"

#include <fstream>

void GameDisplay::initLayout() {
    
    //Reads map file and retrieve cooridnates of the points used to draw the layout
    std::ifstream map("ressources/layout.map"); 
    backgroundTex.loadFromFile("ressources/background_texture.jpg");


    std::vector<sf::Vector2f> layoutPoints;

    float x,y;
    while(map >> x >> y) {
        layoutPoints.push_back(sf::Vector2f(x,y)); 
    }

    map.close();

    // Layout points are assimilited into a VertexArray to create a singular custom drawable
    layout = sf::VertexArray(sf::Quads, layoutPoints.size());

    for (size_t i = 0; i < layoutPoints.size(); ++i) {
        layout[i].texCoords = layoutPoints[i]; // Texture layout
        layout[i].position = layoutPoints[i];
    }


}



void GameDisplay::render(sf::RenderTarget *target) {
    target->draw(layout,&backgroundTex); // renders to window
    game->render(target);
}   

GameDisplay::GameDisplay() {
    initLayout();
    game = new GameGrid();
}