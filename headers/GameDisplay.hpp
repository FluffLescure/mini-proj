#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "GameGrid.hpp"
#include "Config.hpp"
class GameDisplay {
private:
public:

    sf::VertexArray layout;
    GameGrid *game;

    GameDisplay();

    void initLayout();
    void render(sf::RenderTarget *target);
    void update();


};

#endif