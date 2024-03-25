#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "GameGrid.hpp"
class GameDisplay {
private:
public:

    sf::VertexArray layout;
    GameGrid *game;
    sf::Texture backgroundTex;

    GameDisplay();

    void initLayout();
    void render(sf::RenderTarget *target);


};

#endif