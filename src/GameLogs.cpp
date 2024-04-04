#include "../headers/GameLogs.hpp"


GameLogs::GameLogs(){
    gridBorder = sf::RectangleShape(sf::Vector2f(213, 324));
    gridBorder.setPosition(sf::Vector2f(53, 162));
    gridBorder.setOutlineColor(sf::Color(125, 125, 125));
    gridBorder.setOutlineThickness(5);
    gridBorder.setFillColor(sf::Color(0, 0, 0, 0));
}


void GameLogs::render(sf::RenderTarget *target){
    target->draw(gridBorder); // renders the frame
}