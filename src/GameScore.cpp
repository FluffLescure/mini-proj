

#include <SFML/System/Vector2.hpp>

#include "../headers/GameScore.hpp"

GameScore::GameScore() {
    initFrame();
    //initScore();
    //initText();
}

void GameScore::initFrame() {
    scoreFrame = sf::RectangleShape(sf::Vector2f(213, 108));
    scoreFrame.setPosition(sf::Vector2f(693.3, 81));
    scoreFrame.setOutlineColor(sf::Color(125, 125, 125));
    scoreFrame.setOutlineThickness(5);
    scoreFrame.setFillColor(sf::Color(0, 0, 0, 0)); 
}

void GameScore::render(sf::RenderTarget *target){
    target->draw(scoreFrame);
}