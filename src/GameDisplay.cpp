
#include "../headers/GameDisplay.hpp"
#include "../headers/Config.hpp"


void GameDisplay::initLayout() {
    Config* config = Config::getInstance();
    layout = sf::VertexArray(sf::Quads, config->layoutPoints.size());

    // Layout points are assimilited into a VertexArray to create a single
    // custom drawable
    for (size_t i = 0; i < config->layoutPoints.size(); ++i) {
        layout[i].texCoords = config->layoutPoints[i]; // Texture layout
        layout[i].position = config->layoutPoints[i];
    }
}



void GameDisplay::render(sf::RenderTarget *target) {
    target->draw(layout,Config::getInstance()->layoutTex); // renders layout
    game->render(target);
}   

void GameDisplay::update() {
    game->update();
}


GameDisplay::GameDisplay() {
    initLayout();
    game = new GameGrid();
}

GameDisplay::~GameDisplay() {
    delete game;
}