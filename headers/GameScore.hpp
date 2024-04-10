#ifndef GAME_SCORE_HPP
#define GAME_SCORE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>



class GameScore {

private:
    int score;
    sf::RectangleShape scoreFrame;

public:
    GameScore();

    void initFrame();
    void initText();
    void initScore();

    void render(sf::RenderTarget *target);



};

#endif