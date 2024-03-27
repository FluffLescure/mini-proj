#include "../headers/GameDisplay.hpp"

#include <fstream>

void GameDisplay::initLayout() {
 

    // Layout points are assimilited into a VertexArray to create a singular custom drawable
    Config* config = Config::getInstance();

    layout = sf::VertexArray(sf::Quads, config->layoutPoints.size());

    for (size_t i = 0; i < config->layoutPoints.size(); ++i) {
        layout[i].texCoords = config->layoutPoints[i]; // Texture layout
        layout[i].position = config->layoutPoints[i];
    }


}



void GameDisplay::render(sf::RenderTarget *target) {
    target->draw(layout,Config::getInstance()->layoutTex); // renders to window
    game->render(target);
}   

GameDisplay::GameDisplay() {
    initLayout();
    game = new GameGrid();
}