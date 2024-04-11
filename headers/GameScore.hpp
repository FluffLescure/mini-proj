#ifndef GAME_SCORE_HPP
#define GAME_SCORE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>



class GameScore {

private:
    sf::Text scoreVal;
    sf::Text topScoreVal;
    sf::Text scoreText;
    sf::Text topScoreText;

    sf::RectangleShape scoreFrame;



public:
    GameScore();
    ~GameScore();

    void initFrame();
    void initText();
    void initScore();

    void addPoints(std::string word);

    void render(sf::RenderTarget *target);




};

#endif