#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include <SFML/Graphics.hpp>
class GameDisplay {
private:
public:

    sf::VertexArray layout;
    GameDisplay();

    void initLayout();
    void render(sf::RenderTarget *target);


};

#endif