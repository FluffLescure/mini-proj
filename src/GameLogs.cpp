#include "../headers/GameLogs.hpp"
#include "../headers/Config.hpp"


GameLogs::GameLogs(){
    gridBorder = sf::RectangleShape(sf::Vector2f(213, 324));
    gridBorder.setPosition(sf::Vector2f(53, 162));
    gridBorder.setOutlineColor(sf::Color(125, 125, 125));
    gridBorder.setOutlineThickness(5);
    gridBorder.setFillColor(sf::Color(0, 0, 0, 0)); 

    title.setString("Stats");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    title.setFont(*(Config::getInstance()->font));
    title.setOrigin(sf::Vector2f(title.getGlobalBounds().getSize().x / 2.f + title.getLocalBounds().getPosition().x,0));
    title.setPosition(sf::Vector2f(158,162));

    sf::Vector2f tsize;

    for (int i=0;i<10;i++){
        historique[i].setString("Random");
        historique[i].setCharacterSize(18);
        historique[i].setFillColor(sf::Color::White);
        historique[i].setFont(*(Config::getInstance()->font));
        tsize = sf::Vector2f(historique[i].getGlobalBounds().getSize() + historique[i].getLocalBounds().getPosition()); //size of the text
        historique[i].setPosition(sf::Vector2f(63,220+i*(tsize.y+5)));
    }
}


void GameLogs::render(sf::RenderTarget *target){
    target->draw(gridBorder); // renders the frame
    target->draw(title);
    for(int i = 0; i<10; i++){
        target->draw(historique[i]);
    }
}